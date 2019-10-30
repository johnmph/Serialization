//
//  ClassPointerItself.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerItself_hpp
#define ClassPointerItself_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


// Two way to achieve this, first is the best, simply don't serialize the pointer and set/reconstruct it in the constructor / assignment operator
struct ClassPointerItself {
    ClassPointerItself(int data, ClassPointerItself *pointer);
    
private:
    int _data;
    ClassPointerItself *_pointer;
    
    friend bool operator ==(ClassPointerItself const &left, ClassPointerItself const &right);
    friend Serialized<ClassPointerItself>;
};

template <>
struct Serialized<ClassPointerItself> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerItself const &serialized) {
        // For a itself(same than inside) pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        serializer.encode(serialized._data, "dataValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerItself &serialized, int version) {
        // For a itself(same than inside) pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        deserializer.decode(serialized._data, "dataValue");
    }
    
};

// Second is to serialize it, Serialization library will recognize that object pointed is already deserialized and no infinite loop will happen
struct ClassPointerItself2 {
    ClassPointerItself2(int data, ClassPointerItself2 *pointer);
    
private:
    int _data;
    ClassPointerItself2 *_pointer;
    
    friend bool operator ==(ClassPointerItself2 const &left, ClassPointerItself2 const &right);
    friend Serialized<ClassPointerItself2>;
};

template <>
struct Serialized<ClassPointerItself2> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerItself2 const &serialized) {
        // For a itself(same than inside) pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        serializer.encode(serialized._data, "dataValue");
        serializer.encode(serialized._pointer, "pointerValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerItself2 &serialized, int version) {
        // For a itself(same than inside) pointer, don't serialize the pointer, just set/reconstruct it in constructor / assignment operator
        deserializer.decode(serialized._data, "dataValue");
        deserializer.decode(serialized._pointer, "pointerValue"/*, false, { 0, nullptr }*/);
    }
    
};

template <>
inline ClassPointerItself *SerializedDataMakeHeap() {
    return new ClassPointerItself(0, nullptr);
}

template <>
inline ClassPointerItself2 *SerializedDataMakeHeap() {
    return new ClassPointerItself2(0, nullptr);
}

#endif /* ClassPointerItself_hpp */
