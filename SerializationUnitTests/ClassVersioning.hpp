//
//  ClassVersioning.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 4/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassVersioning_hpp
#define ClassVersioning_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassVersioning {
    
    ClassVersioning();
    ClassVersioning(int version, bool boolValue, int intValue);
    
private:
    int _version;
    bool _boolValue;
    int _intValue;
    
    friend bool operator ==(ClassVersioning const &left, ClassVersioning const &right);
    friend Serialized<ClassVersioning>;
};

template <>
struct Serialized<ClassVersioning> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassVersioning const &serialized) {
        serializer.encode(serialized._boolValue, "boolValue");
        
        if (serialized._version == 1) {
            serializer.encode(serialized._intValue, "intValue");
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassVersioning &serialized, int version) {
        serialized._version = version;
        
        deserializer.decode(serialized._boolValue, "boolValue");
        
        if (version == 1) {
            deserializer.decode(serialized._intValue, "intValue");
        }
    }
    
};


#endif /* ClassVersioning_hpp */
