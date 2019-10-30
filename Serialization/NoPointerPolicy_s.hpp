//
//  NoPointerPolicy_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef NoPointerPolicy_s_hpp
#define NoPointerPolicy_s_hpp


template <class TSerializer>
NoPointerEncodePolicy<TSerializer>::NoPointerEncodePolicy(TSerializer &serializer) : _serializer(serializer) {
}

template <class TSerializer>
void NoPointerEncodePolicy<TSerializer>::dataEncoded(void const *dataAddress) {
}

template <class TSerializer>
template <typename TData>
void NoPointerEncodePolicy<TSerializer>::pointerEncoded(TData * const &dataPointer) {
}

template <class TDeserializer>
NoPointerDecodePolicy<TDeserializer>::NoPointerDecodePolicy(TDeserializer &deserializer) : _deserializer(deserializer) {
}

template <class TDeserializer>
void NoPointerDecodePolicy<TDeserializer>::dataDecoded(void *dataAddress) {
}

template <class TDeserializer>
template <typename TData>
void NoPointerDecodePolicy<TDeserializer>::pointerDecoded(TData *decodedPointer, TData * &dataPointer) {
    // Simply copy pointer
    dataPointer = decodedPointer;
}

#endif /* NoPointerPolicy_s_hpp */
