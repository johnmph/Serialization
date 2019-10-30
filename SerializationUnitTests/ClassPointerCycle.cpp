//
//  ClassPointerCycle.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerCycle.hpp"


ClassPointerCycle::ClassPointerCycle(int data, ClassPointerCycle2 *pointer) : _data(data), _pointer(pointer) {
}

ClassPointerCycle::ClassPointerCycle(ClassPointerCycle const &classPointerCycle) : _data(classPointerCycle._data), _pointer(nullptr) {
    if (classPointerCycle._pointer != nullptr) {
        _pointer = new ClassPointerCycle2(*classPointerCycle._pointer);
    }
}

ClassPointerCycle::ClassPointerCycle(ClassPointerCycle &&classPointerCycle) : _data(classPointerCycle._data), _pointer(classPointerCycle._pointer) {
    classPointerCycle._pointer = nullptr;
}

ClassPointerCycle::~ClassPointerCycle() {
    delete _pointer;
}

ClassPointerCycle& ClassPointerCycle::operator=(ClassPointerCycle const &classPointerCycle) {
    if (&classPointerCycle != this) {
        _data = classPointerCycle._data;
        delete _pointer;
        
        if (classPointerCycle._pointer != nullptr) {
            _pointer = new ClassPointerCycle2(*classPointerCycle._pointer);
        } else {
            _pointer = nullptr;
        }
    }
    
    return *this;
}

ClassPointerCycle& ClassPointerCycle::operator=(ClassPointerCycle &&classPointerCycle) {
    if (&classPointerCycle != this) {
        _data = classPointerCycle._data;
        auto p = _pointer;
        _pointer = classPointerCycle._pointer;
        classPointerCycle._pointer = p;
    }
    
    return *this;
}

bool operator ==(ClassPointerCycle const &left, ClassPointerCycle const &right) {
    if (left._data != right._data) {
        return false;
    }
    
    if ((left._pointer == nullptr) || (right._pointer == nullptr)) {
        return left._pointer == right._pointer;
    }
    
    return *left._pointer == *right._pointer;
}

ClassPointerCycle2::ClassPointerCycle2(int data, ClassPointerCycle *pointer) : _data(data), _pointer(pointer) {
}

bool operator ==(ClassPointerCycle2 const &left, ClassPointerCycle2 const &right) {
    if ((left._pointer == nullptr) || (right._pointer == nullptr)) {
        return left._pointer == right._pointer;
    }
    
    return left._data == right._data;
}
