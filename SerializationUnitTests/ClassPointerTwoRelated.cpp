//
//  ClassPointerTwoRelated.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerTwoRelated.hpp"


ClassPointerTwoRelated::ClassPointerTwoRelated(int data, ClassPointerTwoRelated2 *pointer) : _data(data), _pointer(pointer) {
}

void ClassPointerTwoRelated::setPointer(ClassPointerTwoRelated2 *pointer) {
    _pointer = pointer;
}

bool operator ==(ClassPointerTwoRelated const &left, ClassPointerTwoRelated const &right) {
    if (left._data != right._data) {
        return false;
    }
    
    if ((left._pointer == nullptr) || (right._pointer == nullptr)) {
        return left._pointer == right._pointer;
    }
    
    return left._pointer->_data == right._pointer->_data;
}

ClassPointerTwoRelated2::ClassPointerTwoRelated2(int data, ClassPointerTwoRelated *pointer) : _data(data), _pointer(pointer) {
}

bool operator ==(ClassPointerTwoRelated2 const &left, ClassPointerTwoRelated2 const &right) {
    if (left._data != right._data) {
        return false;
    }
    
    if ((left._pointer == nullptr) || (right._pointer == nullptr)) {
        return left._pointer == right._pointer;
    }
    
    return left._pointer->_data == right._pointer->_data;
}
