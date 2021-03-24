#ifndef LIBSTL_UTLITIES_GEOMETRY_HPP
#define LIBSTL_UTLITIES_GEOMETRY_HPP

#include <array>

#include "boolean_operations.hpp"

namespace {

namespace geometry {

template<typename precision>
precision dot_product(const std::array<precision, 3>& u, const std::array<precision, 3>& v) {
    return u.at(0) * v.at(0) + u.at(1) * v.at(1) + u.at(2) * v.at(2);
}

template<typename precision>
std::array<precision, 3> cross_product(const std::array<precision, 3>& u, const std::array<precision, 3>& v) {
    return std::array<precision, 3>({u.at(1) * v.at(2) - u.at(2) * v.at(1), u.at(2) * v.at(0) - u.at(0) * v.at(2),
                                     u.at(0) * v.at(1) - u.at(1) * v.at(0)});
}

template<typename precision>
precision tetrahedron_volume(const std::array<precision, 3>& a, const std::array<precision, 3>& b,
                             const std::array<precision, 3>& c, const std::array<precision, 3>& d) {

    const std::array<precision, 3> a_minus_d = {a.at(0) - d.at(0), a.at(1) - d.at(1), a.at(2) - d.at(2)};
    const std::array<precision, 3> b_minus_d = {b.at(0) - d.at(0), b.at(1) - d.at(1), b.at(2) - d.at(2)};
    const std::array<precision, 3> c_minus_d = {c.at(0) - d.at(0), c.at(1) - d.at(1), c.at(2) - d.at(2)};

    // lacks factor of 1.0 / 6.0 since we are only interested in the sign
    return (dot_product<precision>(a_minus_d, cross_product<precision>(b_minus_d, c_minus_d)));
}

template<typename precision>
bool signed_tetrahedron_volume(const std::array<precision, 3>& a, const std::array<precision, 3>& b,
                               const std::array<precision, 3>& c, const std::array<precision, 3>& d) {
    return (tetrahedron_volume(a, b, c, d) > 0.0) ? true : false;
}

template<typename precision>
bool line_triangle_intersection(const std::array<std::array<precision, 3>, 3>& vertices,
                                const std::array<std::array<precision, 3>, 2>& line_points) {

    const std::array<precision, 3>& q1 = line_points.at(0);
    const std::array<precision, 3>& q2 = line_points.at(1);

    const std::array<precision, 3>& p1 = vertices.at(0);
    const std::array<precision, 3>& p2 = vertices.at(1);
    const std::array<precision, 3>& p3 = vertices.at(2);

    return boolean_operations::exclusive_or(signed_tetrahedron_volume(q1, p1, p2, p3),
                                            signed_tetrahedron_volume(q2, p1, p2, p3)) and
           boolean_operations::equivalence(signed_tetrahedron_volume(q1, q2, p1, p2),
                                           signed_tetrahedron_volume(q1, q2, p2, p3),
                                           signed_tetrahedron_volume(q1, q2, p3, p1));
}

}

}

#endif // LIBSTL_UTLITIES_GEOMETRY_HPP