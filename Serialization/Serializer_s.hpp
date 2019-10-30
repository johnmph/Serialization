//
//  Serializer_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 8/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef Serializer_s_hpp
#define Serializer_s_hpp


template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy>
Serializer<TOstream, TEncoder, TPointerEncodePolicy>::Serializer(TOstream const &ostream) : _encoder(ostream), _pointerEncodePolicy(*this) {
}

template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy>
template <typename TData, typename std::enable_if<(HasSerializedSerialize<TData>::value == true) && (std::is_pointer<TData>::value == false), int>::type>
void Serializer<TOstream, TEncoder, TPointerEncodePolicy>::encode(TData const &data, std::string const &name, int version) {
    // Notify encoder that we start encoding data
    _encoder.startEncode(name, version);    // TODO: passer plutot version a une policy de version ?
    
    // Notify pointer policy that a data is encoded
    _pointerEncodePolicy.dataEncoded(&data);
    
    // Serialize the object itself
    Serialized<TData>::serialize(*this, data);
    
    // Notify encoder that we stop encoding data
    _encoder.stopEncode();
}

template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy>
template <typename TData, typename std::enable_if<(HasSerializedSerialize<TData>::value == false) && (std::is_pointer<TData>::value == false), int>::type>
void Serializer<TOstream, TEncoder, TPointerEncodePolicy>::encode(TData const &data, std::string const &name) {
    // Notify pointer policy that a data is encoded
    _pointerEncodePolicy.dataEncoded(&data);
    
    // Serialize the data itself
    _encoder.encode(data, name);
}

template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy>
template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type>
void Serializer<TOstream, TEncoder, TPointerEncodePolicy>::encode(TData const &dataPointer, std::string const &name) {
    // Notify pointer policy that a data is encoded
    _pointerEncodePolicy.dataEncoded(&dataPointer);
    
    // Encode pointer
    _encoder.encode(dataPointer, name);
    
    // Special case for pointer == nullptr
    if (dataPointer == nullptr) {
        return;
    }
    
    // Notify pointer policy that a pointer is encoded
    _pointerEncodePolicy.pointerEncoded(dataPointer);
}

template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy>
template <typename TData>
void Serializer<TOstream, TEncoder, TPointerEncodePolicy>::encode(TData * const array, std::size_t size, std::string const &name) {
    // Notify pointer policy that a data is encoded
    _pointerEncodePolicy.dataEncoded(array);
    
    // Serialize size of array
    _encoder.encode(size, "size");
    
    // Serialize array
    for (std::size_t i = 0; i < size; ++i) {
        encode(array[i], "value " + std::to_string(i));
    }
}

template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy>
void Serializer<TOstream, TEncoder, TPointerEncodePolicy>::encode(char const * const cstring, std::string const &name) {
    // Notify pointer policy that a data is encoded
    _pointerEncodePolicy.dataEncoded(&cstring);
    
    // Serialize string
    _encoder.encode(cstring, name);
}

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy>
Deserializer<TIstream, TDecoder, TPointerDecodePolicy>::Deserializer(TIstream const &istream) : _decoder(istream), _pointerDecodePolicy(*this) {
}

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy>
template <typename TData, typename std::enable_if<(HasSerializedDeserialize<TData>::value == true) && (std::is_pointer<TData>::value == false), int>::type>
void Deserializer<TIstream, TDecoder, TPointerDecodePolicy>::decode(TData &data, std::string const &name) {
    int version;
    
    // Notify decoder that we start decoding data
    _decoder.startDecode(name, version);
    
    // Notify pointer policy that a data is decoded
    _pointerDecodePolicy.dataDecoded(&data);
    
    // Deserialize the object itself
    Serialized<TData>::deserialize(*this, data, version);
    
    // Notify decoder that we stop decoding data
    _decoder.stopDecode();
}

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy>
template <typename TData, typename std::enable_if<(HasSerializedDeserialize<TData>::value == false) && (std::is_pointer<TData>::value == false), int>::type>
void Deserializer<TIstream, TDecoder, TPointerDecodePolicy>::decode(TData &data, std::string const &name) {
    // Notify pointer policy that a data is decoded
    _pointerDecodePolicy.dataDecoded(&data);
    
    // Deserialize the data itself
    _decoder.decode(data, name);
}

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy>
template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type>
void Deserializer<TIstream, TDecoder, TPointerDecodePolicy>::decode(TData &dataPointer, std::string const &name) {
    // Notify pointer policy that a data is decoded
    _pointerDecodePolicy.dataDecoded(&dataPointer);
    
    // Decode pointer
    TData decodedPointer;
    _decoder.decode(decodedPointer, name);
    
    // Special case for pointer == nullptr
    if (decodedPointer == nullptr) {
        dataPointer = nullptr;
        return;
    }
    
    // Notify pointer policy that a pointer is decoded
    _pointerDecodePolicy.pointerDecoded(decodedPointer, dataPointer);
}

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy>
template <typename TData>
void Deserializer<TIstream, TDecoder, TPointerDecodePolicy>::decode(TData *array, std::size_t &size, std::string const &name) {
    // Notify pointer policy that a data is decoded
    _pointerDecodePolicy.dataDecoded(array);
    
    // Deserialize size of array
    _decoder.decode(size, "size");
    
    // Deserialize array
    for (std::size_t i = 0; i < size; ++i) {
        decode(array[i], "value " + std::to_string(i));
    }
}

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy>
void Deserializer<TIstream, TDecoder, TPointerDecodePolicy>::decode(char *&cstring, std::string const &name) {
    // Notify pointer policy that a data is decoded
    _pointerDecodePolicy.dataDecoded(cstring);
    
    // Deserialize string
    _decoder.decode(cstring, name);
}

#endif /* Serializer_s_hpp */
