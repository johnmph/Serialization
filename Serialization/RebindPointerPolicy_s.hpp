//
//  RebindPointerPolicy_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef RebindPointerPolicy_s_hpp
#define RebindPointerPolicy_s_hpp


template <class TSerializer>
RebindPointerEncodePolicy<TSerializer>::RebindPointerEncodePolicy(TSerializer &serializer) : _serializer(serializer), _dataCount(0) {
}

template <class TSerializer>
RebindPointerEncodePolicy<TSerializer>::~RebindPointerEncodePolicy() {
    savePointedDataAddresses();
}

template <class TSerializer>
void RebindPointerEncodePolicy<TSerializer>::dataEncoded(void const *dataAddress) {
    auto it = _dataAddresses.find(dataAddress);
    
    if (it != _dataAddresses.end()) {
        it->second.first = _dataCount;
    } else {
        _dataAddresses.insert({ dataAddress, { _dataCount, false } });
    }
    
    ++_dataCount;
}

template <class TSerializer>
template <typename TData>
void RebindPointerEncodePolicy<TSerializer>::pointerEncoded(TData * const &dataPointer) {
    auto it = _dataAddresses.find(dataPointer);
    
    if (it != _dataAddresses.end()) {
        it->second.second = true;
    } else {
        _dataAddresses.insert({ dataPointer, { -1, true } });
    }
}

template <class TSerializer>
void RebindPointerEncodePolicy<TSerializer>::savePointedDataAddresses() {
    std::size_t size = 0;
    
    for (auto &p : _dataAddresses) {
        if ((p.second.first != -1) && (p.second.second == true)) {
            ++size;
        }
    }
    
    _serializer._encoder.encode(size, "addresses count");
    
    int i = 0;
    for (auto &p : _dataAddresses) {
        if ((p.second.first != -1) && (p.second.second == true)) {
            // We need to serialize index and address of the object to know which object it is in the deserialization process
            _serializer._encoder.encode(p.second.first, "index " + std::to_string(i));
            _serializer._encoder.encode(p.first, "address " + std::to_string(i));
            
            ++i;
        }
    }
}

template <class TDeserializer>
RebindPointerDecodePolicy<TDeserializer>::RebindPointerDecodePolicy(TDeserializer &deserializer) : _deserializer(deserializer) {
}

template <class TDeserializer>
RebindPointerDecodePolicy<TDeserializer>::~RebindPointerDecodePolicy() {
    rebindPointers();
}

template <class TDeserializer>
//template <typename TData>
void RebindPointerDecodePolicy<TDeserializer>::dataDecoded(void *dataAddress) {
    // Save data address
    _dataAddresses.push_back(dataAddress);
}

template <class TDeserializer>
template <typename TData>
void RebindPointerDecodePolicy<TDeserializer>::pointerDecoded(TData *decodedPointer, TData * &dataPointer) {
    // Save data pointer address
    if (_pointerAddresses.find(decodedPointer) != _pointerAddresses.end()) {
        _pointerAddresses[decodedPointer].first.push_back({ &dataPointer, [=](void *pointer, void *address){ this->setPointerAddress<TData>(pointer, address); } });
    } else {
        _pointerAddresses.insert({ decodedPointer, { { { &dataPointer, [=](void *pointer, void *address){ this->setPointerAddress<TData>(pointer, address); } } }, -1 } });
    }
}

template <class TDeserializer>
template <typename TData>
void RebindPointerDecodePolicy<TDeserializer>::setPointerAddress(void *pointer, void *address) {
    // Safe typed conversion
    *static_cast<TData **>(pointer) = static_cast<TData *>(address);
}

template <class TDeserializer>
void RebindPointerDecodePolicy<TDeserializer>::loadPointedDataAddresses() {
    std::size_t size;
    
    _deserializer._decoder.decode(size);
    
    for (std::size_t i = 0; i < size; ++i) {
        int index;
        
        // Decode index
        _deserializer._decoder.decode(index);
        
        void *dataAddress;
        
        // Decode data address
        _deserializer._decoder.decode(dataAddress);
        
        // Update data index
        _pointerAddresses[dataAddress].second = index;
    }
}

template <class TDeserializer>
void RebindPointerDecodePolicy<TDeserializer>::rebindPointers() {
    loadPointedDataAddresses();
    
    // Update pointers with decoded data address
    for (auto &p : _pointerAddresses) {
        for (auto &p2 : p.second.first) {
            p2.second(p2.first, _dataAddresses[p.second.second]);
        }
    }
}

#endif /* RebindPointerPolicy_s_hpp */
