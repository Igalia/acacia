cmake_minimum_required(VERSION 3.25)

# Enable cmake_print_variables() and cmake_print_properties() for debugging
include(CMakePrintHelpers)

set(PROJECT_LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD 17)

project(
    axaccess
    VERSION 1.0
    LANGUAGES ${PROJECT_LANGUAGES})

# Use absolute paths for #includes
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

add_subdirectory(lib)
add_subdirectory(examples)
