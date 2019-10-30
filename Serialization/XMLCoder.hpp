//
//  XMLCoder.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 20/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef XMLCoder_hpp
#define XMLCoder_hpp

#include "Serialized.hpp"
#include "Serializer.hpp"
#include <sstream>


template <class TOstream>
struct XMLEncoder {
    XMLEncoder(TOstream const &ostream);
    ~XMLEncoder();
    
    void startEncode(std::string const &name, int version);
    void stopEncode();
    
    template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type = 0>
    void encode(TData const &data, std::string const &name = "");
    
private:
    void writeHeader();
    std::string getIndentation();
    
    template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char const *>::value == false, int>::type = 0>
    void correctForEncode(std::string &str);
    
    template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char const *>::value == true, int>::type = 0>
    void correctForEncode(std::string &str);
    
    TOstream _ostream;
    int _currentLevel;
    std::ostringstream _strStream;
    StdOstream _strStdOstream;
};

template <class TIstream>
struct XMLDecoder {
    XMLDecoder(TIstream const &istream);
    
    void startDecode(std::string const &name, int &version);
    void stopDecode();
    
    template <typename TData, typename std::enable_if<(std::is_arithmetic<TData>::value == true) || (std::is_pointer<TData>::value == true), int>::type = 0>
    void decode(TData &data, std::string const &name = "");
    
private:
    void readHeader();
    std::string readString();
    
    template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char *>::value == false, int>::type = 0>
    void correctForDecode(std::string &str);
    
    template <typename TData, typename std::enable_if<std::is_same<typename std::remove_cv<TData>::type, char *>::value == true, int>::type = 0>
    void correctForDecode(std::string &str);
    
    TIstream _istream;
    std::istringstream _strStream;
    StdIstream _strStdIstream;
};


#include "XMLCoder_s.hpp"

#endif /* XMLCoder_hpp */
