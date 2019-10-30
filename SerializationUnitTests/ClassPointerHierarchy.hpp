//
//  ClassPointerHierarchy.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerHierarchy_hpp
#define ClassPointerHierarchy_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


struct ClassPointerHierarchy {
    ClassPointerHierarchy(int data, ClassPointerHierarchy *pointer, bool owner);
    
    ClassPointerHierarchy(ClassPointerHierarchy const &classPointerHierarchy);
    ClassPointerHierarchy(ClassPointerHierarchy &&classPointerHierarchy);
    
    ~ClassPointerHierarchy();
    
    ClassPointerHierarchy& operator=(ClassPointerHierarchy const &classPointerHierarchy);
    ClassPointerHierarchy& operator=(ClassPointerHierarchy &&classPointerHierarchy);
    
private:
    int _data;
    ClassPointerHierarchy *_pointer;
    bool _owner;
    
    friend bool operator ==(ClassPointerHierarchy const &left, ClassPointerHierarchy const &right);
    friend Serialized<ClassPointerHierarchy>;
};

template <>
struct Serialized<ClassPointerHierarchy> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerHierarchy const &serialized) {
        serializer.encode(serialized._data, "dataValue");
        serializer.encode(serialized._owner, "owner");
        
        if (serialized._owner == true) {
            serializer.encode(*serialized._pointer, "pointerValue");
        } else {
            serializer.encode(serialized._pointer, "pointerValue");
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerHierarchy &serialized, int version) {
        deserializer.decode(serialized._data, "dataValue");
        deserializer.decode(serialized._owner, "owner");
        
        if (serialized._owner == true) {
            if (serialized._pointer == nullptr) {
                serialized._pointer = new ClassPointerHierarchy(0, nullptr, false);
            }
            
            deserializer.decode(*serialized._pointer, "pointerValue");
        } else {
            deserializer.decode(serialized._pointer, "pointerValue");
        }
        
        // In case of deserializing a pointer with a class type which don't have default constructor, we need to pass a (temporary) object to (move)copy construct TODO: a voir (si pas de copy/move constructor ?, peut etre plutot passer une lambda de construction d'objet (= [](){ return new std::remove_pointer<TValue>::type(); }
        //serializer.decode(serialized._pointer, "pointerValue"/*, false, { 0, nullptr }*/);
    }
    
};

template <>
inline ClassPointerHierarchy *SerializedDataMakeHeap() {
    return new ClassPointerHierarchy(0, nullptr, false);
}

#endif /* ClassPointerHierarchy_hpp */
