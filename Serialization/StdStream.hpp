//
//  StdStream.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef StdStream_hpp
#define StdStream_hpp

#include <istream>
#include <ostream>


struct StdIstream {
    StdIstream(std::istream &istream);
    
    template <typename TData, typename std::enable_if<std::is_arithmetic<TData>::value == true, int>::type = 0>
    void readText(TData &data);
    
    template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type = 0>
    void readText(TData &data);
    
    template <typename TData>
    void readBinary(TData &data);
    
    void readText(char *&data);
    
    void readBinary(char *&data);
    
private:
    bool readBinary(char *data, int size);
    
    std::istream &_istream;
};

struct StdOstream {
    StdOstream(std::ostream &ostream);
    
    template <typename TData, typename std::enable_if<std::is_arithmetic<TData>::value == true, int>::type = 0>
    void writeText(TData const &data);
    
    template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type = 0>
    void writeText(TData const &data);
    
    template <typename TData>
    void writeBinary(TData const &data);
    
    void writeText(char const *data);
    
    void writeBinary(char const *data);
    
private:
    std::ostream &_ostream;
};


#include "StdStream_s.hpp"

#endif /* StdStream_hpp */
