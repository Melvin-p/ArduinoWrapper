#include <type_traits>

#include "def.hpp"

/*
in cmath the following can be found so cmath can be included for these functions
abs
max
min
pow
sqrt
sin
cos
tan
round
*/

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T constrain(T x, T a, T b) {
    if (x >= a && x <= b) {
        return x;
    } else if (x < a) {
        return a;
    } else {
        return b;
    }
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T radians(T deg) {
    return deg * DEG_TO_RAD;
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T degrees(T deg) {
    return deg * RAD_TO_DEG;
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
T sq(T x) {
    return x * x;
}

long map(long x, long in_min, long in_max, long out_min, long out_max);
