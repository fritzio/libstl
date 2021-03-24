#ifndef LIBSTL_STL_READER_HPP
#define LIBSTL_STL_READER_HPP

#include <string>
#include <vector>
#include <memory>

#include "triangle.hpp"
#include "parser_option.hpp"

#include "utilities/box.hpp"

namespace libstl {

class stl_reader {

    const std::vector<triangle> surface_mesh;

    const utilities::box<float, 3> bounding_box;

    const std::array<float, 3> outside_point;

public:
    template<typename option>
    explicit stl_reader(const std::string& filename, option);

    bool is_inside(const std::array<float, 3> point) const;
    bool is_inside(const float x, const float y, const float z) const;
};

} // namespace stl_reader

#endif // LIBSTL_STL_READER_HPP
