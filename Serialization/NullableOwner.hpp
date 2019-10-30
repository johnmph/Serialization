//
//  NullableOwner.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 1/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef NullableOwner_hpp
#define NullableOwner_hpp

#include <functional>
#include "Serialized.hpp"
#include "Serializer.hpp"


// Nullable owner type
template <typename T>
struct NullableOwner;

template <typename T>
struct NullableOwner<T *> {
    T *&pointer;
    std::function<void(T * &)> resetFunc;
};

template <typename T>
struct NullableOwner<T * const> {
    T * const &pointer;
    std::function<void(T * const &)> resetFunc;
};

template <typename T>
NullableOwner<T *> MakeNullableOwner(T * &pointer, std::function<void(decltype(pointer))> resetFunc = {}) {
    return NullableOwner<T *>{pointer, resetFunc};
}

template <typename T>
NullableOwner<T * const> MakeNullableOwner(T * const &pointer, std::function<void(decltype(pointer))> resetFunc = {}) {
    return NullableOwner<T * const>{pointer, resetFunc};
}

template <typename T>
struct Serialized<NullableOwner<T>> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, NullableOwner<T> const &serialized) {
        // TODO: voir pour tout ce code :
        bool pointerIsValid = serialized.pointer != nullptr;
        serializer.encode(pointerIsValid, "pointerIsValid");
        
        if (pointerIsValid == true) {
            // Encode pointed value
            serializer.encode(*serialized.pointer, "pointer");
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, NullableOwner<T> &serialized, int version) {
        // TODO: voir pour tout ce code :
        bool pointerIsValid;
        deserializer.decode(pointerIsValid, "pointerIsValid");
        
        if (pointerIsValid == true) {
            // Decode pointed value
            deserializer.decode(*serialized.pointer, "pointer");
        } else {
            serialized.resetFunc(serialized.pointer);
        }
    }
    
};

#endif /* NullableOwner_hpp */
