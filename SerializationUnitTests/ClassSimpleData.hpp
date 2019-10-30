//
//  ClassSimpleData.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 14/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassSimpleData_hpp
#define ClassSimpleData_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassSimpleData {
    
    ClassSimpleData();
    ClassSimpleData(bool boolValue, char charValue, short shortValue, int intValue, long longValue, long long longLongValue, float floatValue, double doubleValue, long double longDoubleValue);
    
    bool _boolValue;
    
private:
    char _charValue;
    short _shortValue;
    int _intValue;
    long _longValue;
    long long _longLongValue;
    float _floatValue;
    double _doubleValue;
    long double _longDoubleValue;
    
    friend bool operator ==(ClassSimpleData const &left, ClassSimpleData const &right);
    friend Serialized<ClassSimpleData>;
};

template <>
struct Serialized<ClassSimpleData> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassSimpleData const &serialized) {
        serializer.encode(serialized._boolValue, "boolValue");
        serializer.encode(serialized._charValue, "charValue");
        serializer.encode(serialized._shortValue, "shortValue");
        serializer.encode(serialized._intValue, "intValue");
        serializer.encode(serialized._longValue, "longValue");
        serializer.encode(serialized._longLongValue, "longLongValue");
        serializer.encode(serialized._floatValue, "floatValue");
        serializer.encode(serialized._doubleValue, "doubleValue");
        serializer.encode(serialized._longDoubleValue, "longDoubleValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassSimpleData &serialized, int version) {
        deserializer.decode(serialized._boolValue, "boolValue");
        deserializer.decode(serialized._charValue, "charValue");
        deserializer.decode(serialized._shortValue, "shortValue");
        deserializer.decode(serialized._intValue, "intValue");
        deserializer.decode(serialized._longValue, "longValue");
        deserializer.decode(serialized._longLongValue, "longLongValue");
        deserializer.decode(serialized._floatValue, "floatValue");
        deserializer.decode(serialized._doubleValue, "doubleValue");
        deserializer.decode(serialized._longDoubleValue, "longDoubleValue");
    }
    
};

#endif /* ClassSimpleData_hpp */
