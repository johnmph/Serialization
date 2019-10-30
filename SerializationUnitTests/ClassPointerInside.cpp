//
//  ClassPointerInside.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerInside.hpp"


ClassPointerInside::ClassPointerInside(int data) : _data(data), _pointer(&_data) {
}

ClassPointerInside::ClassPointerInside(ClassPointerInside const &classPointerInside) : _data(classPointerInside._data), _pointer(&_data) {
}

ClassPointerInside::ClassPointerInside(ClassPointerInside &&classPointerInside) : _data(classPointerInside._data), _pointer(&_data) {
}

ClassPointerInside& ClassPointerInside::operator=(ClassPointerInside const &classPointerInside) {
    _data = classPointerInside._data;
    
    return *this;
}

ClassPointerInside& ClassPointerInside::operator=(ClassPointerInside &&classPointerInside) {
    _data = classPointerInside._data;
    
    return *this;
}

bool operator ==(ClassPointerInside const &left, ClassPointerInside const &right) {
    return left._data == right._data;
}
