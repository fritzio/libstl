#include "box.hpp"

template<typename precision, std::size_t dimension>
bool libstl::utilities::box<precision, dimension>::is_inside(const std::array<precision, dimension>& point) const {

    bool is_inside = true;

    for (std::size_t d = 0; d < dimension; ++d) {
        is_inside = ((point.at(d) > min.at(d)) and (point.at(d) < max.at(d))) ? true : false;

        if (is_inside == false) return false;
    }

    return true;
}

template<typename precision, std::size_t dimension>
libstl::utilities::box<precision, dimension>::box(const std::array<precision, dimension>& min,
                                                      const std::array<precision, dimension>& max) :
    min(min),
    max(max) {
    // TODO check if min < max
}

template class libstl::utilities::box<float, 1>;
template class libstl::utilities::box<float, 2>;
template class libstl::utilities::box<float, 3>;

template class libstl::utilities::box<double, 1>;
template class libstl::utilities::box<double, 2>;
template class libstl::utilities::box<double, 3>;

template class libstl::utilities::box<long double, 1>;
template class libstl::utilities::box<long double, 2>;
template class libstl::utilities::box<long double, 3>;