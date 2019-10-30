//
//  ClassPointerData.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 15/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerNew.hpp"


ClassPointerNew::ClassPointerNew(int *pointer) : _pointer(pointer) {
}

ClassPointerNew::ClassPointerNew(ClassPointerNew const &classPointerNew) : _pointer(nullptr) {
    if (classPointerNew._pointer != nullptr) {
        _pointer = new int(*classPointerNew._pointer);
    }
}

ClassPointerNew::ClassPointerNew(ClassPointerNew &&classPointerNew) : _pointer(classPointerNew._pointer) {
    classPointerNew._pointer = nullptr;
}

ClassPointerNew::~ClassPointerNew() {
    delete _pointer;
}

ClassPointerNew& ClassPointerNew::operator=(ClassPointerNew const &classPointerNew) {
    if (&classPointerNew != this) {
        delete _pointer;
        
        if (classPointerNew._pointer != nullptr) {
            _pointer = new int(*classPointerNew._pointer);
        } else {
            _pointer = nullptr;
        }
    }
    
    return *this;
}

ClassPointerNew& ClassPointerNew::operator=(ClassPointerNew &&classPointerNew) {
    if (&classPointerNew != this) {
        auto p = _pointer;
        _pointer = classPointerNew._pointer;
        classPointerNew._pointer = p;
    }
    
    return *this;
}

bool operator ==(ClassPointerNew const &left, ClassPointerNew const &right) {
    if ((left._pointer == nullptr) || (right._pointer == nullptr)) {
        return left._pointer == right._pointer;
    }
    
    return *left._pointer == *right._pointer;
}
