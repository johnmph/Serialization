//
//  Serialized.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 8/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef Serialized_hpp
#define Serialized_hpp

#include <string>


template <class TSerialized, typename Enable = void>
struct Serialized;

/*
 
 Need to be defined like this (for CustomClass) :
 
template <>
struct Serialized<CustomClass> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, CustomClass const &serialized) {
        serializer.encode(serialized.data, "dataName");
        ...
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, CustomClass &serialized, int version) {
        deserializer.decode(serialized.data, "dataName");
        ...
    }
    
};*/

// Function to specialize if TData does not provide default constructors
template <typename TData>
TData SerializedDataMakeStack();

template <typename TData>
TData *SerializedDataMakeHeap();


#include "Serialized_s.hpp"

#endif /* Serialized_hpp */
