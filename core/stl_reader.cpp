#include "stl_reader.hpp"

#include "parser.hpp"
#include "parser_option.hpp"

#include "utilities/geometry.hpp"
#include "utilities/boolean_operations.hpp"

#include <limits>

namespace {

libstl::utilities::box<float, 3> compute_bounding_box(const std::vector<libstl::triangle>& surface_mesh) {

    std::array<float, 3> min;
    std::array<float, 3> max;

    // initialize
    for (auto& _ : min)
        _ = std::numeric_limits<float>::max();
    for (auto& _ : max)
        _ = std::numeric_limits<float>::lowest();

    for (const auto& triangle : surface_mesh) {
        for (const auto& vertex : triangle.vertices) {

            for (std::size_t d = 0; d < 3; ++d) {
                min.at(d) = std::min(min.at(d), vertex.at(d));
                max.at(d) = std::max(max.at(d), vertex.at(d));
            }
        }
    }

    return libstl::utilities::box<float, 3>(min, max);
}

std::array<float, 3> compute_outside_point(const libstl::utilities::box<float, 3>& bounding_box) {

    const float offset = 1.0;

    return {bounding_box.max.at(0) + offset, bounding_box.max.at(1) + offset, bounding_box.max.at(2) + offset};
}

} // namespace

template<typename parser_option>
libstl::stl_reader::stl_reader(const std::string& filename, parser_option) :
    surface_mesh(parse_file(filename, parser_option())),
    bounding_box(compute_bounding_box(surface_mesh)),
    outside_point(compute_outside_point(bounding_box)) {
}

bool libstl::stl_reader::is_inside(const std::array<float, 3> point) const {

    if (!bounding_box.is_inside(point)) return false;

    std::size_t count_intersection = 0;

    for (const auto& triangle : surface_mesh) {
        if (triangle.line_intersects(point, outside_point)) count_intersection++;
    }

    return (boolean_operations::is_odd(count_intersection)) ? true : false;
}

bool libstl::stl_reader::is_inside(const float x, const float y, const float z) const {
    return is_inside({x, y, z});
}

template libstl::stl_reader::stl_reader(const std::string& filename, parser_option::ascii);
template libstl::stl_reader::stl_reader(const std::string& filename, parser_option::binary);