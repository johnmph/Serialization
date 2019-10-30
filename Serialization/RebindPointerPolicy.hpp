//
//  RebindPointerPolicy.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef RebindPointerPolicy_hpp
#define RebindPointerPolicy_hpp

#include <string>
#include <unordered_map>
#include <typeindex>
#include <utility>
#include <functional>


template <class TSerializer>
struct RebindPointerEncodePolicy {
    RebindPointerEncodePolicy(TSerializer &serializer);
    ~RebindPointerEncodePolicy();
    
    // valueAddress is a void * and not a TValue * to avoid problem with TValue = char (TValue * = char * which is interpreted as a string and not as a char pointer by coders), TValue is still provided for informations
    void dataEncoded(void const *dataAddress);
    
    template <typename TData>
    void pointerEncoded(TData * const &dataPointer);
    
private:
    void savePointedDataAddresses();
    
    TSerializer &_serializer;
    
    // Key is data address, value is : first = index of decoded data, second = pointer encoded for this data
    std::unordered_map<void const *, std::pair<int, bool>> _dataAddresses;
    
    // Counter of encoded objects
    int _dataCount;
};

template <class TDeserializer>
struct RebindPointerDecodePolicy {
    RebindPointerDecodePolicy(TDeserializer &deserializer);
    ~RebindPointerDecodePolicy();
    
    // valueAddress is a void * and not a TValue * to avoid problem with TValue = char (TValue * = char * which is interpreted as a string and not as a char pointer by coders), TValue is still provided for informations
    void dataDecoded(void *dataAddress);
    
    template <typename TData>
    void pointerDecoded(TData *decodedPointer, TData * &dataPointer);
    
private:
    template <typename TData>
    void setPointerAddress(void *pointer, void *address);
    
    void loadPointedDataAddresses();
    void rebindPointers();
    
    TDeserializer &_deserializer;
    
    // Vector of decoded data addresses
    std::vector<void *> _dataAddresses;
    
    // Key is decoded pointer value, value is : first = vector (of : first = pointer address, second = type convert function address), second = data index
    std::unordered_map<void *, std::pair<std::vector<std::pair<void *, std::function<void(void *, void *)>>>, int>> _pointerAddresses;
};


#include "RebindPointerPolicy_s.hpp"

#endif /* RebindPointerPolicy_hpp */
