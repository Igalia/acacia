cmake_minimum_required(VERSION 3.25)

# Enable cmake_print_variables() and cmake_print_properties() for debugging
include(CMakePrintHelpers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD 17)

if(WIN32)
  set(PROJECT_LANGUAGES CXX C)
else()
  set(PROJECT_LANGUAGES CXX)
endif()

project(
  axaccess
  VERSION 1.0
  LANGUAGES ${PROJECT_LANGUAGES}
)

# Use absolute paths for #includes
set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories(
  "${BASEPATH}"
  "${BASEPATH}/include"
)

# Feature flags

## Feature flag for cross-platform library, OFF by default
option(
  AXA_LIBAXACCESS
  "Build cross-platform library (experimental)"
  OFF
)

## Feature flag for Python bindings, OFF by default
option(
  AXA_PYTHON_MODULE
  "Build Python bindings (requires swig and python3)"
  OFF
)

## Feature flag for NodeJS bindings, OFF by default
option(
  AXA_NODEJS_MODULE
  "Build NodeJS bindings (requires swig and node-gyp)"
  OFF
)

# On windows, put all of the resulting libraries and executables in
# `build/bin/<CONFIG>` where CONFIG is Debug, Release, etc, because
# windows .dll must be in the same directory as the executables unless
# they are on the path.
# We may decide to solve this problem differently in the future, or use
# the bin for all executables across all platforms.
if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif(WIN32)

add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(third_party)
