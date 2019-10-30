//
//  ClassNoDefaultConstructor.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 11/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassNoDefaultConstructor_hpp
#define ClassNoDefaultConstructor_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassNoDefaultConstructor {
    
    ClassNoDefaultConstructor(int intValue);
    
private:
    int _intValue;
    
    friend bool operator ==(ClassNoDefaultConstructor const &left, ClassNoDefaultConstructor const &right);
    friend Serialized<ClassNoDefaultConstructor>;
};

template <>
struct Serialized<ClassNoDefaultConstructor> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassNoDefaultConstructor const &serialized) {
        serializer.encode(serialized._intValue, "intValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassNoDefaultConstructor &serialized, int version) {
        deserializer.decode(serialized._intValue, "intValue");
    }
    
};

template <>
inline ClassNoDefaultConstructor SerializedDataMakeStack() {
    return ClassNoDefaultConstructor(0);
}

template <>
inline ClassNoDefaultConstructor *SerializedDataMakeHeap() {
    return new ClassNoDefaultConstructor(0);
}

#endif /* ClassNoDefaultConstructor_hpp */
