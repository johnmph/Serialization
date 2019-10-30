//
//  ClassPointerHierarchy.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerHierarchy.hpp"


ClassPointerHierarchy::ClassPointerHierarchy(int data, ClassPointerHierarchy *pointer, bool owner) : _data(data), _pointer(pointer), _owner(owner) {
}

ClassPointerHierarchy::ClassPointerHierarchy(ClassPointerHierarchy const &classPointerHierarchy) : _data(classPointerHierarchy._data), _pointer(classPointerHierarchy._pointer), _owner(classPointerHierarchy._owner) {
    if ((_owner == true) && (_pointer != nullptr)) {
        _pointer = new ClassPointerHierarchy(*_pointer);
    }
}

ClassPointerHierarchy::ClassPointerHierarchy(ClassPointerHierarchy &&classPointerHierarchy) : _data(classPointerHierarchy._data), _pointer(classPointerHierarchy._pointer), _owner(classPointerHierarchy._owner) {
    classPointerHierarchy._pointer = nullptr;
    classPointerHierarchy._owner = false;
}

ClassPointerHierarchy::~ClassPointerHierarchy() {
    if (_owner == true) {
        delete _pointer;
    }
}

ClassPointerHierarchy& ClassPointerHierarchy::operator=(ClassPointerHierarchy const &classPointerHierarchy) {
    if (&classPointerHierarchy != this) {
        _data = classPointerHierarchy._data;
        
        if (_owner == true) {
            delete _pointer;
        }
        
        _owner = classPointerHierarchy._owner;
        _pointer = classPointerHierarchy._pointer;
        
        if ((_owner == true) && (_pointer != nullptr)) {
            _pointer = new ClassPointerHierarchy(*_pointer);
        }
    }
    
    return *this;
}

ClassPointerHierarchy& ClassPointerHierarchy::operator=(ClassPointerHierarchy &&classPointerHierarchy) {
    if (&classPointerHierarchy != this) {
        _data = classPointerHierarchy._data;
        
        if (_owner == true) {
            delete _pointer;
        }
        
        _owner = classPointerHierarchy._owner;
        _pointer = classPointerHierarchy._pointer;
        
        classPointerHierarchy._pointer = nullptr;
        classPointerHierarchy._owner = false;
    }
    
    return *this;
}

bool operator ==(ClassPointerHierarchy const &left, ClassPointerHierarchy const &right) {
    if (left._data != right._data) {
        return false;
    }
    
    if (left._owner != right._owner) {
        return false;
    }
    
    if ((left._pointer == nullptr) || (right._pointer == nullptr)) {
        return left._pointer == right._pointer;
    }
    
    return *left._pointer == *right._pointer;
}
