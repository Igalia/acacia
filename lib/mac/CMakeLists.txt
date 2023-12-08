# Target macOS 13 or later
# https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

add_library(
  # Name
  mac_inspect

  # Sources
  axapi_node.cc
)

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
cmake_print_variables(APPLICATION_SERVICES_FRAMEWORK)

target_include_directories(
  mac_inspect

  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
  mac_inspect

  PUBLIC
    ${APPLICATION_SERVICES_FRAMEWORK}
)

# SWIG Instructions to build a python module called "mac_inspect"

find_package(SWIG COMPONENTS python)
include(UseSWIG)

find_package(Python3 COMPONENTS Interpreter Development)

include_directories(${Python3_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_property(SOURCE mac_inspect.i PROPERTY CPLUSPLUS ON)

swig_add_library(
  # The name of the c++ library used by python module
  mac_python_inspect
  TYPE SHARED
  LANGUAGE python
  SOURCES mac_inspect.i
)

set_target_properties(
  mac_python_inspect

  PROPERTIES
  SUFFIX .so
)

target_link_libraries(
  # Target to link
  mac_python_inspect

  # Items to link into the target
  mac_inspect
  ${Python3_LIBRARIES}
)

set_property(
  TARGET mac_python_inspect
  PROPERTY
    SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
)

