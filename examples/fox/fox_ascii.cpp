#include "stl_reader.hpp"

#include <iostream>

int main(void) {

    std::string filename = "../examples/fox/fox_ascii.stl";

    const auto mesh = libstl::stl_reader(filename, libstl::parser_option::ascii());

    constexpr float x_min = 30.0;
    constexpr float x_max = 120.0;

    constexpr float y_min = 30.0;
    constexpr float y_max = 120.0;

    constexpr float z_min = 0.0;
    constexpr float z_max = 125.0;

    constexpr float h = 2.0; // grid spacing

    constexpr std::size_t nx = static_cast<std::size_t>((x_max - x_min) / h);
    constexpr std::size_t ny = static_cast<std::size_t>((y_max - y_min) / h);
    constexpr std::size_t nz = static_cast<std::size_t>((z_max - z_min) / h);

    bool tag[nx][ny][nz];

    for (std::size_t i = 0; i < nx; ++i) {

        const float x = x_min + (0.5 + static_cast<float>(i)) * h;

        for (std::size_t j = 0; j < ny; ++j) {

            const float y = y_min + (0.5 + static_cast<float>(j)) * h;

            for (std::size_t k = 0; k < nz; ++k) {

                const float z = z_min + (0.5 + static_cast<float>(k)) * h;

                tag[i][j][k] = mesh.is_inside(x, y, z);
            }
        }
    }

    const std::size_t i = static_cast<std::size_t>((70 - x_min) / h);

    for (std::size_t k = nz - 1; k != 0; --k) {

        for (std::size_t j = 0; j < ny; ++j) {

            std::cout << ((tag[i][j][k]) ? "o" : ".");
            std::cout << " ";
        }

        std::cout << "\n";
    }

    return 0;
}