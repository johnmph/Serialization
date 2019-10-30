//
//  BinaryCoder_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 9/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef BinaryCoder_s_hpp
#define BinaryCoder_s_hpp


template <class TOstream>
BinaryEncoder<TOstream>::BinaryEncoder(TOstream const &ostream) : _ostream(ostream) {
}

template <class TOstream>
void BinaryEncoder<TOstream>::startEncode(std::string const &name, int version) {
    encode(version, name);
}

template <class TOstream>
void BinaryEncoder<TOstream>::stopEncode() {
}

template <class TOstream>
template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type>
void BinaryEncoder<TOstream>::encode(TData const &data, std::string const &name) {
    _ostream.writeBinary(data);
}

template <class TIstream>
BinaryDecoder<TIstream>::BinaryDecoder(TIstream const &istream) : _istream(istream) {
}

template <class TIstream>
void BinaryDecoder<TIstream>::startDecode(std::string const &name, int &version) {
    decode(version, name);
}

template <class TIstream>
void BinaryDecoder<TIstream>::stopDecode() {
}

template <class TIstream>
template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type>
void BinaryDecoder<TIstream>::decode(TData &data, std::string const &name) {
    _istream.readBinary(data);
}

#endif /* BinaryCoder_s_hpp */
