//
//  ClassPointerOutside.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerOutside.hpp"


ClassPointerOutside::ClassPointerOutside(int data, int *pointer) : _data(data), _pointer(pointer) {
}

bool operator ==(ClassPointerOutside const &left, ClassPointerOutside const &right) {
    if (left._pointer != right._pointer) {
        return false;
    }
    
    return left._data == right._data;
}
