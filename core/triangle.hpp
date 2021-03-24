#ifndef LIBSTL_TRIANGLE_HPP
#define LIBSTL_TRIANGLE_HPP

#include <array>

namespace libstl {

class triangle {

public:
    const std::array<std::array<float, 3>, 3> vertices;

    explicit triangle(const std::array<std::array<float, 3>, 3> vertices);
    explicit triangle(const std::array<float, 3> x, const std::array<float, 3> y, const std::array<float, 3> z);
    explicit triangle(const float (&x)[3], const float (&y)[3], const float (&z)[3]);

    bool line_intersects(const std::array<float, 3> p, const std::array<float, 3> q) const;
};

} // namespace libstl

#endif // LIBSTL_TRIANGLE_HPP