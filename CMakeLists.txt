cmake_minimum_required(VERSION 3.6)

PROJECT(libstl VERSION 0.0.1)

MESSAGE(STATUS "LIBSTL_VERSION : ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS, "-Werror -Wall -Wextra")

INCLUDE(cmake/options.cmake)

INCLUDE_DIRECTORIES(core)

# build library
IF(LIBSTL_BUILD_LIB)
    ADD_SUBDIRECTORY(core)
ENDIF()

# build examples
IF(LIBSTL_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()