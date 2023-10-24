cmake_minimum_required(VERSION 3.10)

project(
  axaccess
  VERSION 1.0
  LANGUAGES CXX)

# Use absolute paths for #includes
SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")

add_subdirectory(lib)