cmake_minimum_required(VERSION 3.10)

project(
  axaccess
  VERSION 1.0
  LANGUAGES CXX)

add_library(
  atspi
  atspi/atspi.cc
  atspi/atspi.h
)
add_executable(
  main atspi/test.cc
)
target_link_libraries(main PRIVATE atspi)
