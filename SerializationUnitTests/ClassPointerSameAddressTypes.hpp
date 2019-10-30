//
//  ClassPointerSameAddressTypes.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 3/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef ClassPointerSameAddressTypes_hpp
#define ClassPointerSameAddressTypes_hpp

#include "ClassSimpleData.hpp"


struct ClassPointerSameAddressTypes {
    
    ClassPointerSameAddressTypes();
    ClassPointerSameAddressTypes(ClassSimpleData *pSimpleData, bool *pBool);
    
private:
    ClassSimpleData *_pSimpleData;
    bool *_pBool;
    
    friend bool operator ==(ClassPointerSameAddressTypes const &left, ClassPointerSameAddressTypes const &right);
    friend Serialized<ClassPointerSameAddressTypes>;
};

template <>
struct Serialized<ClassPointerSameAddressTypes> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, ClassPointerSameAddressTypes const &serialized) {
        serializer.encode(serialized._pSimpleData, "pSimpleData");
        serializer.encode(serialized._pBool, "pBool");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, ClassPointerSameAddressTypes &serialized, int version) {
        deserializer.decode(serialized._pSimpleData, "pSimpleData");
        deserializer.decode(serialized._pBool, "pBool");
    }
    
};

#endif /* ClassPointerSameAddressTypes_hpp */
