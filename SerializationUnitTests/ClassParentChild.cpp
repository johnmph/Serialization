//
//  ClassParentChild.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 13/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassParentChild.hpp"


ClassParent::ClassParent() : _intValue(0) {
}

ClassParent::ClassParent(int intValue) : _intValue(intValue) {
}

int ClassParent::test() {
    return 1;
}

ClassChild::ClassChild() : _boolValue(false) {
}

ClassChild::ClassChild(bool boolValue, int intValue) : _boolValue(boolValue), ClassParent(intValue) {
}

int ClassChild::test() {
    return 1;
}

bool operator ==(ClassParent const &left, ClassParent const &right) {
    return (left._intValue == right._intValue);
}

bool operator ==(ClassChild const &left, ClassChild const &right) {
    return (left._boolValue == right._boolValue) && (static_cast<ClassParent>(left) == static_cast<ClassParent>(right));
}
