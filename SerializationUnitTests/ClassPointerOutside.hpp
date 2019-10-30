//
//  ClassPointerOutside.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerOutside_hpp
#define ClassPointerOutside_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassPointerOutside {
    ClassPointerOutside(int data, int *pointer);
    
private:
    int _data;
    int *_pointer;
    
    friend bool operator ==(ClassPointerOutside const &left, ClassPointerOutside const &right);
    friend Serialized<ClassPointerOutside>;
};

template <>
struct Serialized<ClassPointerOutside> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerOutside const &serialized) {
        // For a outside pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        serializer.encode(serialized._data, "dataValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerOutside &serialized, int version) {
        // For a outside pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        deserializer.decode(serialized._data, "dataValue");
    }
    
};

#endif /* ClassPointerOutside_hpp */
