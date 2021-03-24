#include "triangle.hpp"

#include <algorithm>
#include <array>

#include "utilities/geometry.hpp"

namespace {

template<typename precision, std::size_t dimension>
std::array<precision, dimension> convert_array(const precision (&u)[dimension]) {
    std::array<precision, 3> v;
    std::copy(std::begin(u), std::end(u), std::begin(v));
    return v;
}

} // namespace

libstl::triangle::triangle(const std::array<std::array<float, 3>, 3> vertices) : vertices(vertices) {
}

libstl::triangle::triangle(const std::array<float, 3> x, const std::array<float, 3> y,
                               const std::array<float, 3> z) :
    vertices({x, y, z}) {
}

libstl::triangle::triangle(const float (&x)[3], const float (&y)[3], const float (&z)[3]) :
    vertices({convert_array<float, 3>(x), convert_array<float, 3>(y), convert_array<float, 3>(z)}) {
}

bool libstl::triangle::line_intersects(const std::array<float, 3> p, const std::array<float, 3> q) const {
    return geometry::line_triangle_intersection<float>(vertices, {p, q});
}