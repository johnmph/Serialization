//
//  StdStream_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef StdStream_s_hpp
#define StdStream_s_hpp


bool isLittleEndian();
void switchNativeBigEndian(char *buffer, std::size_t size);

template <typename TData, typename std::enable_if<std::is_arithmetic<TData>::value == true, int>::type>
void StdIstream::readText(TData &data) {
    _istream >> data;
}

template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type>
void StdIstream::readText(TData &data) {
    void *pointer;
    
    _istream >> pointer;
    data = static_cast<TData>(pointer);
}

template <typename TData>
void StdIstream::readBinary(TData &data) {
    //_istream.read(reinterpret_cast<char *>(&data), sizeof(data));
    
    // Avoid UB (type pun + alignment) ( https://gist.github.com/shafik/848ae25ee209f698763cffee272a58f8 )
    alignas(alignof(TData)) char dataPun[sizeof(TData)];
    _istream.read(dataPun, sizeof(TData));
    switchNativeBigEndian(dataPun, sizeof(TData));
    std::memcpy(&data, dataPun, sizeof(TData));
}

template <typename TData, typename std::enable_if<std::is_arithmetic<TData>::value == true, int>::type>
void StdOstream::writeText(TData const &data) {
    _ostream << data;
}

template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type>
void StdOstream::writeText(TData const &data) {
    _ostream << static_cast<void const *>(data);
}

template <typename TData>
void StdOstream::writeBinary(TData const &data) {
    //_ostream.write(reinterpret_cast<char const *>(&data), sizeof(data));
    
    // Avoid UB (type pun + alignment) ( https://gist.github.com/shafik/848ae25ee209f698763cffee272a58f8 )
    alignas(alignof(TData)) char dataPun[sizeof(TData)];
    std::memcpy(dataPun, &data, sizeof(TData));
    switchNativeBigEndian(dataPun, sizeof(TData));
    _ostream.write(dataPun, sizeof(TData));
}

#endif /* StdStream_s_hpp */
