//
//  ClassPointerInside.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerInside_hpp
#define ClassPointerInside_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassPointerInside {
    ClassPointerInside(int data);
    
    ClassPointerInside(ClassPointerInside const &classPointerInside);
    ClassPointerInside(ClassPointerInside &&classPointerInside);
    
    ClassPointerInside& operator=(ClassPointerInside const &classPointerInside);
    ClassPointerInside& operator=(ClassPointerInside &&classPointerInside);
    
private:
    int _data;
    int *_pointer;
    
    friend bool operator ==(ClassPointerInside const &left, ClassPointerInside const &right);
    friend Serialized<ClassPointerInside>;
};

template <>
struct Serialized<ClassPointerInside> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerInside const &serialized) {
        // For a inside pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        serializer.encode(serialized._data, "dataValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerInside &serialized, int version) {
        // For a inside pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        deserializer.decode(serialized._data, "dataValue");
    }
    
};

#endif /* ClassPointerInside_hpp */
