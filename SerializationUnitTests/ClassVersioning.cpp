//
//  ClassVersioning.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 4/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassVersioning.hpp"


ClassVersioning::ClassVersioning() : _version(0), _boolValue(false), _intValue(0) {
}

ClassVersioning::ClassVersioning(int version, bool boolValue, int intValue) : _version(version), _boolValue(boolValue), _intValue(intValue) {
}

bool operator ==(ClassVersioning const &left, ClassVersioning const &right) {
    return (left._boolValue == right._boolValue) && (((left._version == 0) && (right._version == 0)) || (left._intValue == right._intValue));
}
