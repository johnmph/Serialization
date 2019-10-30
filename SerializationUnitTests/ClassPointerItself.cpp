//
//  ClassPointerItself.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerItself.hpp"


ClassPointerItself::ClassPointerItself(int data, ClassPointerItself *pointer) : _data(data), _pointer(pointer) {
}

bool operator ==(ClassPointerItself const &left, ClassPointerItself const &right) {
    if ((left._pointer != &left) || (right._pointer != &right)) {
        return false;
    }
    
    return left._data == right._data;
}

ClassPointerItself2::ClassPointerItself2(int data, ClassPointerItself2 *pointer) : _data(data), _pointer(pointer) {
}

bool operator ==(ClassPointerItself2 const &left, ClassPointerItself2 const &right) {
    if ((left._pointer != &left) || (right._pointer != &right)) {
        return false;
    }
    
    return left._data == right._data;
}
