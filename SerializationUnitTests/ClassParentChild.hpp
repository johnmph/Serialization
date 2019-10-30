//
//  ClassParentChild.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 13/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassParentChild_hpp
#define ClassParentChild_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassParent {
    
    ClassParent();
    ClassParent(int intValue);
    
    virtual ~ClassParent() = default;
    
    virtual int test();
    
private:
    int _intValue;
    
    friend bool operator ==(ClassParent const &left, ClassParent const &right);
    friend Serialized<ClassParent>;
};

struct ClassChild : ClassParent {
    
    ClassChild();
    ClassChild(bool boolValue, int intValue);
    
    virtual int test() override;
    
private:
    bool _boolValue;
    
    friend bool operator ==(ClassChild const &left, ClassChild const &right);
    friend Serialized<ClassChild>;
};

template <>
struct Serialized<ClassParent> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassParent const &serialized) {
        serializer.encode(serialized._intValue, "intValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassParent &serialized, int version) {
        deserializer.decode(serialized._intValue, "intValue");
    }
    
};

template <>
struct Serialized<ClassChild> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassChild const &serialized) {
        serializer.template encode<ClassParent>(serialized);
        serializer.encode(serialized._boolValue, "boolValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassChild &serialized, int version) {
        deserializer.template decode<ClassParent>(serialized);
        deserializer.decode(serialized._boolValue, "boolValue");
    }
    
};

#endif /* ClassParentChild_hpp */
