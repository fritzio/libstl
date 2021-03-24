#include "stl_reader.hpp"

#include <iostream>

// using namespace libstl;

int main(void) {

    std::string filename = "../examples/lizard/lizard.stl";

    const auto mesh = libstl::stl_reader(filename, libstl::parser_option::binary());

    constexpr float x_min = -50.0;
    constexpr float x_max =  50.0;

    constexpr float y_min = -50.0;
    constexpr float y_max =  50.0;

    constexpr float z_min = -50.0;
    constexpr float z_max =  50.0;

    constexpr float h = 2.0; // grid spacing

    constexpr std::size_t nx = static_cast<std::size_t>((x_max - x_min) / h);
    constexpr std::size_t ny = static_cast<std::size_t>((y_max - y_min) / h);
    constexpr std::size_t nz = static_cast<std::size_t>((z_max - z_min) / h);

    bool tag[nx][ny][nz];

    // #pragma omp parallel for collapse(3)
    for (std::size_t i = 0; i < nx; ++i) {
        for (std::size_t j = 0; j < ny; ++j) {
            for (std::size_t k = 0; k < nz; ++k) {

                // compute the coordinates of the current grid point
                const float x = x_min + (0.5 + static_cast<float>(i)) * h;
                const float y = y_min + (0.5 + static_cast<float>(j)) * h;
                const float z = z_min + (0.5 + static_cast<float>(k)) * h;

                // populate the tag with a boolean which indicates if the grid point lies within the mesh
                tag[i][j][k] = mesh.is_inside(x, y, z);
            }
        }
    }


    std::cout << "x" << "," << "y" << "," << "z" << "," << "tag" << std::endl;

    for (std::size_t i = 0; i < nx; ++i) {
        for (std::size_t j = 0; j < ny; ++j) {
            for (std::size_t k = 0; k < nz; ++k) {

                const float x = x_min + (0.5 + static_cast<float>(i)) * h;
                const float y = y_min + (0.5 + static_cast<float>(j)) * h;
                const float z = z_min + (0.5 + static_cast<float>(k)) * h;

                std::cout << x << "," << y << "," << z << "," << tag[i][j][k] << std::endl;
            }
        }
    }

    return 0;
}