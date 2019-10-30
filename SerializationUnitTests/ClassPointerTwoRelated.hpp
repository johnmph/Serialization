//
//  ClassPointerTwoRelated.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerTwoRelated_hpp
#define ClassPointerTwoRelated_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassPointerTwoRelated2;

struct ClassPointerTwoRelated {
    ClassPointerTwoRelated(int data, ClassPointerTwoRelated2 *pointer);
    
    void setPointer(ClassPointerTwoRelated2 *pointer);
    
private:
    int _data;
    ClassPointerTwoRelated2 *_pointer;
    
    friend bool operator ==(ClassPointerTwoRelated const &left, ClassPointerTwoRelated const &right);
    friend Serialized<ClassPointerTwoRelated>;
    friend bool operator ==(ClassPointerTwoRelated2 const &left, ClassPointerTwoRelated2 const &right);
};

struct ClassPointerTwoRelated2 {
    ClassPointerTwoRelated2(int data, ClassPointerTwoRelated *pointer);
    
private:
    int _data;
    ClassPointerTwoRelated *_pointer;
    
    friend bool operator ==(ClassPointerTwoRelated2 const &left, ClassPointerTwoRelated2 const &right);
    friend Serialized<ClassPointerTwoRelated2>;
    friend bool operator ==(ClassPointerTwoRelated const &left, ClassPointerTwoRelated const &right);
};

template <>
struct Serialized<ClassPointerTwoRelated> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerTwoRelated const &serialized) {
        serializer.encode(serialized._data, "dataValue");
        serializer.encode(serialized._pointer, "pointerValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerTwoRelated &serialized, int version) {
        deserializer.decode(serialized._data, "dataValue");
        deserializer.decode(serialized._pointer, "pointerValue"/*, false, { 0, nullptr }*/);
    }
    
};

template <>
struct Serialized<ClassPointerTwoRelated2> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerTwoRelated2 const &serialized) {
        serializer.encode(serialized._data, "dataValue");
        serializer.encode(serialized._pointer, "pointerValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerTwoRelated2 &serialized, int version) {
        deserializer.decode(serialized._data, "dataValue");
        deserializer.decode(serialized._pointer, "pointerValue"/*, false, { 0, nullptr }*/);
    }
    
};

template <>
inline ClassPointerTwoRelated *SerializedDataMakeHeap() {
    return new ClassPointerTwoRelated(0, nullptr);
}

template <>
inline ClassPointerTwoRelated2 *SerializedDataMakeHeap() {
    return new ClassPointerTwoRelated2(0, nullptr);
}

#endif /* ClassPointerTwoRelated_hpp */
