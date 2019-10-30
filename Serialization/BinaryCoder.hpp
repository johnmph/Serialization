//
//  BinaryCoder.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 9/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef BinaryCoder_hpp
#define BinaryCoder_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


template <class TOstream>
struct BinaryEncoder {
    BinaryEncoder(TOstream const &ostream);
    
    void startEncode(std::string const &name, int version);
    void stopEncode();
    
    template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type = 0>
    void encode(TData const &data, std::string const &name = "");
    
private:
    TOstream _ostream;
};

template <class TIstream>
struct BinaryDecoder {
    BinaryDecoder(TIstream const &istream);
    
    void startDecode(std::string const &name, int &version);
    void stopDecode();
    
    template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type = 0>
    void decode(TData &data, std::string const &name = "");
    
private:
    TIstream _istream;
};


#include "BinaryCoder_s.hpp"

#endif /* BinaryCoder_hpp */
