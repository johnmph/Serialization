//
//  TextCoder_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 9/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef TextCoder_s_hpp
#define TextCoder_s_hpp


template <class TOstream>
TextEncoder<TOstream>::TextEncoder(TOstream const &ostream) : _ostream(ostream) {
}

template <class TOstream>
void TextEncoder<TOstream>::startEncode(std::string const &name, int version) {
    encode(version, name);
}

template <class TOstream>
void TextEncoder<TOstream>::stopEncode() {
}

template <class TOstream>
template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type>
void TextEncoder<TOstream>::encode(TData const &data, std::string const &name) {
    _ostream.writeText(data);
    
    // Append new line
    _ostream.writeBinary('\n');
}

template <class TIstream>
TextDecoder<TIstream>::TextDecoder(TIstream const &istream) : _istream(istream) {
}

template <class TIstream>
void TextDecoder<TIstream>::startDecode(std::string const &name, int &version) {
    decode(version, name);
}

template <class TIstream>
void TextDecoder<TIstream>::stopDecode() {
}

template <class TIstream>
template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type>
void TextDecoder<TIstream>::decode(TData &data, std::string const &name) {
    _istream.readText(data);
    
    // Read new line '\n'
    char c;
    _istream.readBinary(c);
}

#endif /* TextCoder_s_hpp */
