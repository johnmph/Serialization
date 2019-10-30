//
//  RebuildPointerPolicy.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 16/09/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef RebuildPointerPolicy_hpp
#define RebuildPointerPolicy_hpp

#include <string>
#include <unordered_set>
#include <unordered_map>
// TODO: c'est dans cette policy qu'on doit se charger des classes meres / classes filles avec un pointer parent car dans les autres policy on ne recrée pas les objets, on ne fait que deserializer dans ceux deja existants (oui mais meme dans l'autre policy ca posera probleme car le type statique reste la classe mere et donc il faut faire un dynamic_cast dans le code de serialization / deserialization) : Avoir une classe /fonction template a specializer qui donnera l'identifiant des classes (pour enregistrer une classe, il suffira de specialiser la classe / fonction avec la classe)

template <class TSerializer>
struct RebuildPointerEncodePolicy {
    RebuildPointerEncodePolicy(TSerializer &serializer);
    
    void dataEncoded(void const *dataAddress);
    
    template <typename TData>
    void pointerEncoded(TData * const &dataPointer);
    
private:
    TSerializer &_serializer;
    std::unordered_set<void const *> _serializedObjectAddressSet;            // TODO: Pour le serialize, voir quand le reset
};

template <class TDeserializer>
struct RebuildPointerDecodePolicy {
    RebuildPointerDecodePolicy(TDeserializer &deserializer);
    
    void dataDecoded(void *dataAddress);
    
    template <typename TData>
    void pointerDecoded(TData *decodedPointer, TData * &dataPointer);
    
private:
    TDeserializer &_deserializer;
    std::unordered_map<void *, void *> _deserializedObjectAddressMap;    // TODO: Pour le deserialize, voir quand le reset
};


#include "RebuildPointerPolicy_s.hpp"

#endif /* RebuildPointerPolicy_hpp */
