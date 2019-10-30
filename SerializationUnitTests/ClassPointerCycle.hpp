//
//  ClassPointerCycle.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerCycle_hpp
#define ClassPointerCycle_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassPointerCycle2;

struct ClassPointerCycle {
    ClassPointerCycle(int data, ClassPointerCycle2 *pointer);
    
    ClassPointerCycle(ClassPointerCycle const &classPointerCycle);
    ClassPointerCycle(ClassPointerCycle &&classPointerCycle);
    
    ~ClassPointerCycle();
    
    ClassPointerCycle& operator=(ClassPointerCycle const &classPointerCycle);
    ClassPointerCycle& operator=(ClassPointerCycle &&classPointerCycle);
    
private:
    int _data;
    ClassPointerCycle2 *_pointer;
    
    friend bool operator ==(ClassPointerCycle const &left, ClassPointerCycle const &right);
    friend Serialized<ClassPointerCycle>;
};

struct ClassPointerCycle2 {
    ClassPointerCycle2(int data, ClassPointerCycle *pointer);
    
private:
    int _data;
    ClassPointerCycle *_pointer;
    
    friend bool operator ==(ClassPointerCycle2 const &left, ClassPointerCycle2 const &right);
    friend Serialized<ClassPointerCycle2>;
};

template <>
struct Serialized<ClassPointerCycle> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerCycle const &serialized) {
        serializer.encode(serialized._data, "dataValue");
        serializer.encode(*serialized._pointer, "pointerValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerCycle &serialized, int version) {
        deserializer.decode(serialized._data, "dataValue");
        // In case of deserializing a pointer with a class type which don't have default constructor, we need to pass a (temporary) object to (move)copy construct TODO: a voir (si pas de copy/move constructor ?, peut etre plutot passer une lambda de construction d'objet (= [](){ return new std::remove_pointer<TValue>::type(); }
        if (serialized._pointer == nullptr) {
            serialized._pointer = new ClassPointerCycle2(0, nullptr);
        }
        
        deserializer.decode(*serialized._pointer, "pointerValue"/*, false, { 0, nullptr }*/);
    }
    
};

template <>
struct Serialized<ClassPointerCycle2> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerCycle2 const &serialized) {
        serializer.encode(serialized._data, "dataValue");
        serializer.encode(serialized._pointer, "pointerValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerCycle2 &serialized, int version) {
        deserializer.decode(serialized._data, "dataValue");
        // In case of deserializing a pointer with a class type which don't have default constructor, we need to pass a (temporary) object to (move)copy construct TODO: a voir (si pas de copy/move constructor ?, peut etre plutot passer une lambda de construction d'objet (= [](){ return new std::remove_pointer<TValue>::type(); }
        deserializer.decode(serialized._pointer, "pointerValue"/*, false, { 0, nullptr }*/);
    }
    
};

template <>
inline ClassPointerCycle *SerializedDataMakeHeap() {
    return new ClassPointerCycle(0, nullptr);
}

template <>
inline ClassPointerCycle2 *SerializedDataMakeHeap() {
    return new ClassPointerCycle2(0, nullptr);
}

#endif /* ClassPointerCycle_hpp */
