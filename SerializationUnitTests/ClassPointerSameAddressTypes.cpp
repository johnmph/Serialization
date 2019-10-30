//
//  ClassPointerSameAddressTypes.cpp
//  SerializationUnitTests
//
//  Created by Jonathan Baliko on 3/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "ClassPointerSameAddressTypes.hpp"


ClassPointerSameAddressTypes::ClassPointerSameAddressTypes() : _pSimpleData(nullptr), _pBool(nullptr) {
}

ClassPointerSameAddressTypes::ClassPointerSameAddressTypes(ClassSimpleData *pSimpleData, bool *pBool) : _pSimpleData(pSimpleData), _pBool(pBool) {
}

bool operator ==(ClassPointerSameAddressTypes const &left, ClassPointerSameAddressTypes const &right) {
    return (*left._pSimpleData == *right._pSimpleData) && (*left._pBool == *right._pBool);
}
