//
//  FloatComparaison.hpp
//  TestStatistics
//
//  Created by Jonathan Baliko on 7/04/19.
//  Copyright © 2019 Jonathan Baliko. All rights reserved.
//

/*
 Taken from here : https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */

#ifndef FloatComparaison_hpp
#define FloatComparaison_hpp

#include <cmath>

// TODO: voir ici aussi : https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
namespace FloatComparaison {//TODO: faire des tests pour ces fonctions et voir ulp !
    
    template <typename ValueType>
    typename std::enable_if<!std::numeric_limits<ValueType>::is_integer, bool>::type almost_equal(ValueType x, ValueType y, int ulp = 1) {
        // The machine epsilon has to be scaled to the magnitude of the values used and multiplied by the desired precision in ULPs (units in the last place) unless the result is subnormal
        return (std::abs(x - y) <= (std::numeric_limits<ValueType>::epsilon() * std::abs(x + y) * ulp)) || (std::abs(x - y) < std::numeric_limits<ValueType>::min());
    }
    
    template <typename ValueType>
    typename std::enable_if<!std::numeric_limits<ValueType>::is_integer, bool>::type almost_zero(ValueType x, int ulp = 1) {
        return almost_equal(x, static_cast<ValueType>(0), ulp);
    }
    
}

#endif /* FloatComparaison_hpp */
