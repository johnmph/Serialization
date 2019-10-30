//
//  StdSmartPtr.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 26/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef StdSmartPtr_hpp
#define StdSmartPtr_hpp

#include <memory>
#include "Serialized.hpp"
#include "Serializer.hpp"


template <typename T, class Deleter>
struct Serialized<std::unique_ptr<T, Deleter>> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, std::unique_ptr<T, Deleter> const &serialized) {
        // TODO: voir pour tout ce code :
        bool pointerIsValid = serialized != nullptr;
        serializer.encode(pointerIsValid, "pointerIsValid");
        
        if (pointerIsValid == true) {
            // Encode pointed value
            serializer.encode(*serialized, "pointer");
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, std::unique_ptr<T, Deleter> &serialized, int version) {
        // TODO: voir pour tout ce code :
        bool pointerIsValid;
        deserializer.decode(pointerIsValid, "pointerIsValid");
        
        if (pointerIsValid == true) {
            // Decode pointed value
            deserializer.decode(*serialized, "pointer");
        } else {
            serialized.reset(nullptr);
        }
    }
    
};

template <typename T>
struct Serialized<std::weak_ptr<T>> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, std::weak_ptr<T> const &serialized) {
        T *pointer = serialized.lock().get();
        
        serializer.encode(pointer, "pointer");
    }
    /*
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, std::weak_ptr<T> &serialized, int version) {
        T *pointer;
        
        deserializer.decode(pointer, "pointer");
        serialized = std::shared_ptr<T>(pointer);//TODO: ce n'est pas bon
    }*/
    
};


#endif /* StdSmartPtr_hpp */
