//
//  StdStream.cpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#include "StdStream.hpp"


bool isLittleEndian() {
    int16_t volatile check = 0x1234;
    return reinterpret_cast<char volatile *>(&check)[0] == 0x34;
}

void switchNativeBigEndian(char *buffer, std::size_t size) {
    // Check native endian
    if (isLittleEndian() == false) {
        return;
    }
    
    for (std::size_t i = 0; i < (size >> 1); ++i) {
        std::swap(buffer[i], buffer[(size - 1) - i]);
    }
}

StdIstream::StdIstream(std::istream &istream) : _istream(istream) {
}

void StdIstream::readText(char *&data) {
    // TODO: assert data == nullptr ?
    
    // Read null terminated string
    readBinary(data);
}

void StdIstream::readBinary(char *&data) {
    // TODO: assert data == nullptr ?
    
    int size = 128;
    data = static_cast<char *>(std::malloc(size * sizeof(char)));
    
    for (int i = 0;;) {
        bool ok = readBinary(&data[i], size - i);
        if (ok == true) {
            break;
        }
        
        i = size;
        size *= 2;
        data = static_cast<char *>(std::realloc(data, size * sizeof(char)));
    }
}

bool StdIstream::readBinary(char *data, int size) {
    for (std::size_t i = 0; i < size; ++i) {
        _istream.read(&data[i], sizeof(char));
        
        if (data[i] == 0) {
            return true;
        }
    }
    
    return false;
}

StdOstream::StdOstream(std::ostream &ostream) : _ostream(ostream) {
}

void StdOstream::writeText(char const *data) {
    // Write null terminated string
    writeBinary(data);
}

void StdOstream::writeBinary(char const *data) {
    _ostream.write(data, std::strlen(data) + 1);
}

