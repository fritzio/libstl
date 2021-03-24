#ifndef LIBSTL_UTLITIES_BOX_HPP
#define LIBSTL_UTLITIES_BOX_HPP

#include <array>

namespace libstl {

namespace utilities {

template<typename precision, std::size_t dimension>
class box {

    // check if the precision is a floating-point type - otherwise give a compilation error
    static_assert(std::is_floating_point<precision>::value, "Provided template-argument is not a floating-point type");

    // check if the dimension is one, two or three - otherwise give a compilation error
    static_assert(dimension <= 3 or dimension >= 1, "Provided template-argument is not supported");

public:
    const std::array<precision, dimension> min;
    const std::array<precision, dimension> max;

    bool is_inside(const std::array<precision, dimension>& point) const;

    explicit box(const std::array<precision, dimension>& min, const std::array<precision, dimension>& max);
};

} // namespace utilities

} // namespace libstl

#endif // LIBSTL_UTLITIES_BOX_HPP