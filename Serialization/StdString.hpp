//
//  StdString.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 18/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef StdString_hpp
#define StdString_hpp

#include <string>
#include "Serialized.hpp"
#include "Serializer.hpp"


template <>
struct Serialized<std::string> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, std::string const &serialized) {
        serializer.encode(serialized.c_str(), "data");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, std::string &serialized, int version) {
        char *temp = nullptr;
        
        deserializer.decode(temp, "data");
        serialized = temp;
        
        std::free(temp);
    }
    
};

#endif /* StdString_hpp */
