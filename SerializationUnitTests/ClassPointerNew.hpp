//
//  ClassPointerNew.hpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 15/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerNew_hpp
#define ClassPointerNew_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"
#include "NullableOwner.hpp"


struct ClassPointerNew {
    ClassPointerNew(int *pointer);
    
    ClassPointerNew(ClassPointerNew const &classPointerNew);
    ClassPointerNew(ClassPointerNew &&classPointerNew);
    
    ~ClassPointerNew();
    
    ClassPointerNew& operator=(ClassPointerNew const &classPointerNew);
    ClassPointerNew& operator=(ClassPointerNew &&classPointerNew);
    
private:
    int *_pointer;
    
    friend bool operator ==(ClassPointerNew const &left, ClassPointerNew const &right);
    friend Serialized<ClassPointerNew>;
};

template <>
struct Serialized<ClassPointerNew> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerNew const &serialized) {
        //serializer.encode(serialized._data, "dataValue");       // Besoin d'encoder lui avant le pointer si le pointeur pointe vers lui sinon il va sauver 2x le data
        /*
        bool pointerValueOk = serialized._pointer != nullptr;
        
        serializer.encode(pointerValueOk, "pointerValueOk", true);
        if (pointerValueOk == true) {
            serializer.encode(*serialized._pointer, "pointerValue");
        }*/
        serializer.encode(MakeNullableOwner(serialized._pointer), "pointerValue");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerNew &serialized, int version) {
        //deserializer.decode(serialized._data, "dataValue");
        /*
        bool pointerValueOk;
        deserializer.decode(pointerValueOk, "pointerValueOk", true);
        
        if (pointerValueOk == true) {
            deserializer.decode(*serialized._pointer, "pointerValue");
        } else {
            delete serialized._pointer;
            serialized._pointer = nullptr;
        }*/
        
        auto markOwner = MakeNullableOwner(serialized._pointer, [] (int * &pointer) {
            delete pointer;
            pointer = nullptr;
        });
        deserializer.decode(/*MakeNullableOwner(serialized._pointer)*/markOwner, "pointerValue");
    }
    
};

#endif /* ClassPointerNew_hpp */
