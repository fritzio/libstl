#ifndef LIBSTL_UTLITIES_BOOLEAN_OPERATIONS_HPP
#define LIBSTL_UTLITIES_BOOLEAN_OPERATIONS_HPP

#include <array>

namespace {

namespace boolean_operations {

bool exclusive_or(const bool x, const bool y) {
    return (x xor y);
}

bool equivalence(const bool x, const bool y, const bool z) {
    return (x and y and z) or ((not x) and (not y) and (not z));
}

template<typename T>
bool is_odd(const T t) {
    return (t % 2) == 1;
}

template<typename T>
bool is_even(const T t) {
    return (t % 2) == 0;
}

} // namespace boolean_operations

} // namespace

#endif // LIBSTL_UTLITIES_BOOLEAN_OPERATIONS_HPP