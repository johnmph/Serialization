//
//  RebuildPointerPolicy_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef RebuildPointerPolicy_s_hpp
#define RebuildPointerPolicy_s_hpp


template <class TSerializer>
RebuildPointerEncodePolicy<TSerializer>::RebuildPointerEncodePolicy(TSerializer &serializer) : _serializer(serializer) {
}

template <class TSerializer>
void RebuildPointerEncodePolicy<TSerializer>::dataEncoded(void const *dataAddress) {
    // We need to store address of each serialized object in case of some pointers on these objects need also to be serialized
    _serializedObjectAddressSet.insert(dataAddress);
    
    // We need to serialize also address of the object to know which object it is in the deserialization process
    _serializer._encoder.encode(dataAddress, "address");
}

template <class TSerializer>
template <typename TData>
void RebuildPointerEncodePolicy<TSerializer>::pointerEncoded(TData * const &dataPointer) {
    if (_serializedObjectAddressSet.find(dataPointer) == _serializedObjectAddressSet.end()) {
        // Encode pointed data
        _serializer.encode(*dataPointer);
    }
}

template <class TDeserializer>
RebuildPointerDecodePolicy<TDeserializer>::RebuildPointerDecodePolicy(TDeserializer &deserializer) : _deserializer(deserializer) {
}

template <class TDeserializer>
void RebuildPointerDecodePolicy<TDeserializer>::dataDecoded(void *dataAddress) {
    // Deserialize address of the object
    void *decodedAddress;
    _deserializer._decoder.decode(decodedAddress, "address");
    
    // We need to store address of each deserialized object in case of some pointers on these objects need also to be deserialized
    //_deserializedObjectAddressMap.insert({ decodedAddress, dataAddress });
    _deserializedObjectAddressMap[decodedAddress] = dataAddress;  // TODO: on utilise cette ecriture plutot que celle du dessus pour overrider les possibles doublons pour permettre la technique du decodage manuel (size dynamique) des arrays
}

template <class TDeserializer>
template <typename TData>
void RebuildPointerDecodePolicy<TDeserializer>::pointerDecoded(TData *decodedPointer, TData * &dataPointer) {
    if (_deserializedObjectAddressMap.find(decodedPointer) == _deserializedObjectAddressMap.end()) {
        // Create data
        TData *data = SerializedDataMakeHeap<TData>();
        _deserializedObjectAddressMap.insert({ decodedPointer, data });
        
        // Decode pointed data
        _deserializer.decode(*data);
    }
    
    dataPointer = static_cast<TData *>(_deserializedObjectAddressMap[decodedPointer]);
}

#endif /* RebuildPointerPolicy_s_hpp */
