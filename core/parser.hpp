#ifndef LIBSTL_PARSER_HPP
#define LIBSTL_PARSER_HPP

#include <fstream>
#include <string>
#include <vector>

#include "triangle.hpp"
#include "parser_option.hpp"

#include "utilities/string.hpp"

#include <iostream>

namespace libstl {

namespace {

std::vector<triangle> parse_file(const std::string& filename, parser_option::ascii) {

    std::vector<triangle> surface_mesh;

    auto file = std::ifstream(filename);

    if (file.is_open()) {

        std::string line;

        std::size_t i = 0;
        std::array<std::array<float, 3>, 3> coordinatex;

        while (std::getline(file, line)) {

            // find all lines which contain the "vertex" keyword
            if (line.find("vertex") != std::string::npos) {

                line = utilities::string::erase(line, "vertex");
                // std::cout << line << std::endl;

                const auto _ = utilities::string::trim_and_split(line);

                std::array<float, 3> vertex = {std::stof(_.at(0)), std::stof(_.at(1)), std::stof(_.at(2))};

                coordinatex.at(i) = vertex;

                // for (std::size_t d = 0; d < 3; d++) {
                //     coordinatex.at(i).at(d) = utilities::cast::to_precision<double>(_.at(d));
                // }

                // for(const auto& _ : utilities::string::trim_and_split(line)) {
                // }

                if (i==2) {
                    surface_mesh.push_back(triangle(coordinatex));
                }

                i = (i == 2) ? 0 : (i + 1);

            }

        }

        //

        file.close();

    } else {
        throw std::invalid_argument("Could not open ASCII STL file");
    }

    return surface_mesh;
}

std::vector<triangle> parse_file(const std::string& filename, parser_option::binary) {

    std::vector<triangle> surface_mesh;

    auto file = std::ifstream(filename, std::ios::in | std::ios::binary);

    if (file.is_open()) {

        // skip the first 80 bytes for the header
        file.seekg(80, std::ios::beg);

        // read number of triangles into a 4 byte long buffer
        std::uint32_t number_of_triangles;
        file.read((char*) &number_of_triangles, 4);


        for (std::uint32_t i = 0; i < number_of_triangles; ++i) {

            // anonymous struct to read the raw data
            struct {
                float normal[3];
                float v1[3];
                float v2[3];
                float v3[3];
                std::uint16_t attribute;
            } binary_triangle;

            // the size of the struct is hard-coded in order to avoid padding
            file.read((char*) &binary_triangle, 50);

            surface_mesh.push_back(triangle(binary_triangle.v1, binary_triangle.v2, binary_triangle.v3));

        }

        file.close();

    } else {
        throw std::invalid_argument("Could not open binary STL file");
    }

    return surface_mesh;
}

}

} // namespace LIBSTL

#endif // LIBSTL_PARSER_HPP