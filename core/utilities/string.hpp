#ifndef LIBSTL_UTLITIES_STRING_HPP
#define LIBSTL_UTLITIES_STRING_HPP

#include <array>
#include <string>
#include <vector>

namespace libstl {

namespace utilities {

namespace string {

std::string erase(const std::string& string, const std::string& substring) {
    std::string s = string;
    return s.erase(string.find(substring), substring.length());
}

std::string trim_leading_whitespace(const std::string& string, const std::string whitespace = " ") {
    return string.substr(string.find_first_not_of(whitespace));
}

std::string trim_trailing_whitespace(const std::string& string, const std::string whitespace = " ") {
    return string.substr(0, string.find_last_not_of(whitespace) + 1);
}

std::vector<std::string> split(const std::string& string, const std::string delimiter = " ") {

    std::vector<std::string> splitted_string;

    std::string s   = string;
    std::size_t pos = 0;

    while ((pos = s.find(delimiter)) != std::string::npos) {

        std::string token = s.substr(0, pos);

        splitted_string.push_back(token);

        s.erase(0, pos + delimiter.length());
    }

    splitted_string.push_back(s);

    return splitted_string;
}

std::vector<std::string> trim_and_split(const std::string& string, const std::string delimiter = " ",
                                               const std::string whitespace = " ") {
    return split(trim_trailing_whitespace(trim_leading_whitespace(string, whitespace), whitespace), delimiter);
}

} // namespace string

} // namespace utilities

} // namespace libstl

#endif // LIBSTL_UTLITIES_STRING_HPP