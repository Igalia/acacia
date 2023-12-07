cmake_minimum_required(VERSION 3.25)

set(PROJECT_LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if(APPLE)
  list(APPEND PROJECT_LANGUAGES Swift)
endif()

project(
    axaccess
    VERSION 1.0
    LANGUAGES ${PROJECT_LANGUAGES})

# Use absolute paths for #includes
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

SET(GENERATED_FILES_BASEPATH "${CMAKE_BINARY_DIR}/generated")
INCLUDE_DIRECTORIES("${GENERATED_FILES_BASEPATH}")

add_subdirectory(lib)
add_subdirectory(examples)
