//
//  ClassComposition.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 7/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassComposition.hpp"


ClassComposition::ClassComposition() : _boolValue(false), _intValue(0) {
}

ClassComposition::ClassComposition(bool boolValue, ClassSimpleData classSimpleDataValue, int intValue) : _boolValue(boolValue), _classSimpleDataValue(classSimpleDataValue), _intValue(intValue) {
}

bool operator ==(ClassComposition const &left, ClassComposition const &right) {
    return (left._boolValue == right._boolValue) && (left._classSimpleDataValue == right._classSimpleDataValue) && (left._intValue == right._intValue);
}
