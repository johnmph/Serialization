//
//  TextCoder.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 9/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef TextCoder_hpp
#define TextCoder_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"


template <class TOstream>
struct TextEncoder {
    TextEncoder(TOstream const &ostream);
    
    void startEncode(std::string const &name, int version);
    void stopEncode();
    
    template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type = 0>
    void encode(TData const &data, std::string const &name = "");
    
private:
    TOstream _ostream;
};

template <class TIstream>
struct TextDecoder {
    TextDecoder(TIstream const &istream);
    
    void startDecode(std::string const &name, int &version);
    void stopDecode();
    
    template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type = 0>
    void decode(TData &data, std::string const &name = "");
    
private:
    TIstream _istream;
};


#include "TextCoder_s.hpp"

#endif /* TextCoder_hpp */
