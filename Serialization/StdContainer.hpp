//
//  StdContainer.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 17/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef StdContainer_hpp
#define StdContainer_hpp

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include "Serialized.hpp"
#include "Serializer.hpp"


// This type traits check if type is a std container (not specialized for std::array and std::forward_list because they need special implementations)
template <typename T>
struct IsStdContainer : std::false_type {
};

template <typename... Args>
struct IsStdContainer<std::vector<Args...>> : std::true_type {
};

template <typename... Args>
struct IsStdContainer<std::deque<Args...>> : std::true_type {
};

template <typename... Args>
struct IsStdContainer<std::list<Args...>> : std::true_type {
};

template <typename... Args>
struct IsStdContainer<std::set<Args...>> : std::true_type {
};

template <typename... Args>
struct IsStdContainer<std::map<Args...>> : std::true_type {
};

template <typename... Args>
struct IsStdContainer<std::unordered_set<Args...>> : std::true_type {
};

template <typename... Args>
struct IsStdContainer<std::unordered_map<Args...>> : std::true_type {
};


// Need this type traits to remove const from std::pair of (unordered_)map
template <typename T>
struct RemoveCV : std::remove_cv<T> {
};

template <typename... Args>
struct RemoveCV<std::pair<Args...>> {
    using type = std::pair<typename RemoveCV<Args>::type...>;
};


template <typename T, std::size_t Size>
struct Serialized<std::array<T, Size>> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, std::array<T, Size> const &serialized) {
        using SizeType = typename std::array<T, Size>::size_type;
        
        serializer.encode(Size, "size");
        
        SizeType i = 0;
        for (auto it = serialized.begin(); it != serialized.end(); ++it, ++i) {
            serializer.encode(*it, "value " + std::to_string(i));
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, std::array<T, Size> &serialized, int version) {
        using SizeType = typename std::array<T, Size>::size_type;
        
        SizeType size;
        deserializer.decode(size, "size");
        
        // TODO: throw if size != Size ?
        
        for (SizeType i = 0; i < size; ++i) {
            deserializer.decode(serialized[i], "value " + std::to_string(i));
        }
    }
    
};

template <class TContainer>
struct Serialized<TContainer, typename std::enable_if<IsStdContainer<TContainer>::value>::type> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, TContainer const &serialized) {
        using SizeType = typename TContainer::size_type;
        
        serializer.encode(serialized.size(), "size");
        
        SizeType i = 0;
        for (auto it = serialized.begin(); it != serialized.end(); ++it, ++i) {
            serializer.encode(*it, "value " + std::to_string(i));
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, TContainer &serialized, int version) {
        using SizeType = typename TContainer::size_type;
        
        SizeType size;
        deserializer.decode(size, "size");
        
        for (SizeType i = 0; i < size; ++i) {
            auto value = SerializedDataMakeStack<typename RemoveCV<typename TContainer::value_type>::type>();
            
            deserializer.decode(value, "value " + std::to_string(i));
            serialized.insert(serialized.end(), value);
        }
    }
    
};

template <typename T>
struct Serialized<std::forward_list<T>> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, std::forward_list<T> const &serialized) {
        using SizeType = typename std::forward_list<T>::size_type;
        
        SizeType size = 0;
        
        for (auto it = serialized.begin(); it != serialized.end(); ++it) {
            ++size;
        }
        
        serializer.encode(size, "size");
        
        SizeType i = 0;
        for (auto it = serialized.begin(); it != serialized.end(); ++it, ++i) {
            serializer.encode(*it, "value " + std::to_string(i));
        }
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, std::forward_list<T> &serialized, int version) {
        using SizeType = typename std::forward_list<T>::size_type;
        
        SizeType size;
        deserializer.decode(size, "size");
        
        auto it = serialized.before_begin();
        for (SizeType i = 0; i < size; ++i) {
            T value = SerializedDataMakeStack<T>();
            
            deserializer.decode(value, "value " + std::to_string(i));
            it = serialized.insert_after(it, value);
        }
    }
    
};

template <typename T1, typename T2>
struct Serialized<std::pair<T1, T2>> {
    
    template <class TSerializer>
    static void serialize(TSerializer &serializer, std::pair<T1, T2> const &serialized) {
        serializer.encode(serialized.first, "first");
        serializer.encode(serialized.second, "second");
    }
    
    template <class TDeserializer>
    static void deserialize(TDeserializer &deserializer, std::pair<T1, T2> &serialized, int version) {
        deserializer.decode(serialized.first, "first");
        deserializer.decode(serialized.second, "second");
    }
    
};

#endif /* StdContainer_hpp */
