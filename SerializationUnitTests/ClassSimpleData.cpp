//
//  ClassSimpleData.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 14/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassSimpleData.hpp"
#include "FloatComparaison.hpp"


ClassSimpleData::ClassSimpleData() : _boolValue(false), _charValue('a'), _shortValue(0), _intValue(0), _longValue(0), _longLongValue(0), _floatValue(0), _doubleValue(0), _longDoubleValue(0) {
}

ClassSimpleData::ClassSimpleData(bool boolValue, char charValue, short shortValue, int intValue, long longValue, long long longLongValue, float floatValue, double doubleValue, long double longDoubleValue) : _boolValue(boolValue), _charValue(charValue), _shortValue(shortValue), _intValue(intValue), _longValue(longValue), _longLongValue(longLongValue), _floatValue(floatValue), _doubleValue(doubleValue), _longDoubleValue(longDoubleValue) {
}

bool operator ==(ClassSimpleData const &left, ClassSimpleData const &right) {
    return (left._boolValue == right._boolValue) && (left._charValue == right._charValue) && (left._shortValue == right._shortValue) && (left._intValue == right._intValue) && (left._longValue == right._longValue) && (left._longLongValue == right._longLongValue) && FloatComparaison::almost_equal(left._floatValue, right._floatValue) && FloatComparaison::almost_equal(left._doubleValue, right._doubleValue) && FloatComparaison::almost_equal(left._longDoubleValue, right._longDoubleValue, 1000);
}
