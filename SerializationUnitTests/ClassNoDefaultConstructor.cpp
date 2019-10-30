//
//  ClassNoDefaultConstructor.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 11/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassNoDefaultConstructor.hpp"


ClassNoDefaultConstructor::ClassNoDefaultConstructor(int intValue) : _intValue(intValue) {
}

bool operator ==(ClassNoDefaultConstructor const &left, ClassNoDefaultConstructor const &right) {
    return (left._intValue == right._intValue);
}
