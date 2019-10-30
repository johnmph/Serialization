//
//  ClassComposition.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 7/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassComposition_hpp
#define ClassComposition_hpp

#include "ClassSimpleData.hpp"


struct ClassComposition {
    
    ClassComposition();
    ClassComposition(bool boolValue, ClassSimpleData classSimpleDataValue, int intValue);
    
private:
    bool _boolValue;
    ClassSimpleData _classSimpleDataValue;
    int _intValue;
    
    friend bool operator ==(ClassComposition const &left, ClassComposition const &right);
    friend Serialized<ClassComposition>;
};

template <>
struct Serialized<ClassComposition> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassComposition const &serialized) {
        serializer.encode(serialized._boolValue, "boolValue");
        serializer.encode(serialized._classSimpleDataValue, "classSimpleDataValue");
        serializer.encode(serialized._intValue, "intValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassComposition &serialized, int version) {
        deserializer.decode(serialized._boolValue, "boolValue");
        deserializer.decode(serialized._classSimpleDataValue, "classSimpleDataValue");
        deserializer.decode(serialized._intValue, "intValue");
    }
    
};

#endif /* ClassComposition_hpp */
