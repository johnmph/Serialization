//
//  Serialized_s.hpp
//  Serialization
//
//  Created by Jonathan Baliko on 11/10/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

#ifndef Serialized_s_hpp
#define Serialized_s_hpp


template <typename TData>
TData SerializedDataMakeStack() {
    return TData();
}

template <typename TData>
TData *SerializedDataMakeHeap() {
    return new TData();
}

#endif /* Serialized_s_hpp */
