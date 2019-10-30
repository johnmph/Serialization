//
//  NoPointerPolicy.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef NoPointerPolicy_hpp
#define NoPointerPolicy_hpp

#include <string>


template <class TSerializer>
struct NoPointerEncodePolicy {
    NoPointerEncodePolicy(TSerializer &serializer);
    
    void dataEncoded(void const *dataAddress);
    
    template <typename TData>
    void pointerEncoded(TData * const &dataPointer);
    
private:
    TSerializer &_serializer;
};

template <class TDeserializer>
struct NoPointerDecodePolicy {
    NoPointerDecodePolicy(TDeserializer &deserializer);
    
    void dataDecoded(void *dataAddress);
    
    template <typename TData>
    void pointerDecoded(TData *decodedPointer, TData * &dataPointer);
    
private:
    TDeserializer &_deserializer;
};


#include "NoPointerPolicy_s.hpp"

#endif /* NoPointerPolicy_hpp */
