//
//  Serializer.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 8/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef Serializer_hpp
#define Serializer_hpp

#include <string>
// TODO: par apres, se débarrasser des c-string et c-array et mettre dans le core les std containers std string

// Traits to know if a class has a serializer (serialize methods)
template <typename T, bool = true>
struct HasSerializedSerialize : std::false_type {};

template <typename T>
struct HasSerializedSerialize<T, (sizeof(decltype(&Serialized<T>::template serialize<void *>)) >= 0)> : std::true_type {};

// Traits to know if a class has a deserializer (deserialize methods)
template <typename T, bool = true>
struct HasSerializedDeserialize : std::false_type {};

template <typename T>
struct HasSerializedDeserialize<T, (sizeof(decltype(&Serialized<T>::template deserialize<void *>)) >= 0)> : std::true_type {};


template <class TOstream, template <class> class TEncoder, template <class> class TPointerEncodePolicy> // Comme dans modern c++ design pour separer orthogonalement les fonctionnalités, selon le format les données ne doivent pas etre forcement traitées sequentiellement (xml par exemple), donc il doit avoir un lien entre format et flux ?
// TODO: peut etre deriver de TPointerPolicy plutot que de l'avoir en membre pour heriter de ses methodes, a voir
// TODO: voir pour l'ecriture des methodes avec les parametres optionnel car une chaine de caractere peut etre convertie en bool donc faire attention !!!!
//TODO: voir pour les cycles, pour les smart ptr, ... : TODO: voir pour les pointeurs de pointeurs !!!
// TODO: rajouter un reset ou un finish ? qui se propage dans les stream, decoder et policy ?
struct Serializer {
    
    Serializer(TOstream const &ostream);
    
    template <typename TData, typename std::enable_if<(HasSerializedSerialize<TData>::value == true) && (std::is_pointer<TData>::value == false), int>::type = 0>
    void encode(TData const &data, std::string const &name = "", int version = 0);
    
    template <typename TData, typename std::enable_if<(HasSerializedSerialize<TData>::value == false) && (std::is_pointer<TData>::value == false), int>::type = 0>
    void encode(TData const &data, std::string const &name = "");
    
    template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type = 0>
    void encode(TData const &dataPointer, std::string const &name = "");
    
    template <typename TData>
    void encode(TData * const array, std::size_t size, std::string const &name = "");
    
    void encode(char const * const cstring, std::string const &name = "");
    
private:
    // Order matter for the destructor (because pointer policy destructor can call encoder method)
    TEncoder<TOstream> _encoder;
    TPointerEncodePolicy<Serializer> _pointerEncodePolicy;
    
    friend TPointerEncodePolicy<Serializer>;
};

template <class TIstream, template <class> class TDecoder, template <class> class TPointerDecodePolicy> // TODO: pareil que Serializer pour les commentaires
struct Deserializer {
    
    Deserializer(TIstream const &istream);
    
    template <typename TData, typename std::enable_if<(HasSerializedDeserialize<TData>::value == true) && (std::is_pointer<TData>::value == false), int>::type = 0>
    void decode(TData &data, std::string const &name = "");
    
    template <typename TData, typename std::enable_if<(HasSerializedDeserialize<TData>::value == false) && (std::is_pointer<TData>::value == false), int>::type = 0>
    void decode(TData &data, std::string const &name = "");
    
    template <typename TData, typename std::enable_if<std::is_pointer<TData>::value == true, int>::type = 0>
    void decode(TData &dataPointer, std::string const &name = "");
    
    template <typename TData>
    void decode(TData *array, std::size_t &size, std::string const &name = "");
    
    void decode(char *&cstring, std::string const &name = "");
    
private:
    // Order matter for the destructor (because pointer policy destructor can call decoder method)
    TDecoder<TIstream> _decoder;
    TPointerDecodePolicy<Deserializer> _pointerDecodePolicy;
    
    friend TPointerDecodePolicy<Deserializer>;
};


#include "Serializer_s.hpp"

#endif /* Serializer_hpp */
