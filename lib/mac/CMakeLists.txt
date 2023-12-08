# Swift/C++ CMake configuration based heavily on
# https://github.com/apple/swift-cmake-examples/blob/main/3_bidirectional_cxx_interop/

# Verify that we have a new enough compiler
if("${CMAKE_Swift_COMPILER_VERSION}" VERSION_LESS 5.9)
  message(FATAL_ERROR "Bidirectional C++ Interop requires Swift 5.9 or greater. Have ${CMAKE_Swift_COMPILER_VERSION}")
endif()

# Check that we're using clang
if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND
   NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  message(FATAL_ERROR "Project requires building with Clang. Have ${CMAKE_CXX_COMPILER_ID}")
endif()

# Target macOS 13 or later
# https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

# Add current source dir to module path so that we can find
# InitializeSwift.cmake and AddSwift.cmake to include below
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Set up swiftrt.o and runtime library search paths
include(InitializeSwift)
# cmake/modules/AddSwift.cmake provides the function for creating the Swift to
# C++ bridging header
include(AddSwift)

# Set up a list called MAC_INSPECT_SOURCES which will be used by both the
# Swift-only library and the C++ header generation rule
list(APPEND MAC_INSPECT_SOURCES
  axapi_node.cc
)

# The C++ header generation rule requires a path relative to the project root,
# so create a copy of MAC_INSPECT_SOURCES with the current source dir prepended
# to each
# list(TRANSFORM MAC_INSPECT_SOURCES
#   PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/"
#   OUTPUT_VARIABLE MAC_INSPECT_SOURCES_FULL_PATH
# )

# # Generated C++ header for the Swift library
# _swift_generate_cxx_header_target(
#   # Target name
#   mac_inspect_swift_h

#   # SwiftModule/C++ namespace
#   MacInspect

#   # Generated header output path
#   "${GENERATED_FILES_BASEPATH}/include/axaccess/mac/mac_inspect.h"

#   # Sources (keyword argument)
#   SOURCES "${MAC_INSPECT_SOURCES_FULL_PATH}"
# )

add_library(
  # Name
  mac_inspect

  # Sources
  ${MAC_INSPECT_SOURCES}
)

# Manually set the Swift module name for the mac_inspect module to match the
# module name used in the header generation above
# set_target_properties(mac_inspect PROPERTIES Swift_MODULE_NAME "MacInspect")

# Include the header generation as a dependency so that the header is available
# to users of the library
# add_dependencies(mac_inspect mac_inspect_swift_h)

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
# Make sure SWIG (and other users of the mac_inspect library) can find the
# generated header file
# target_include_directories(
#   mac_inspect

#   PUBLIC
#     "${GENERATED_FILES_BASEPATH}/include"
# )

# When building mac_inspect, enable C++ interoperability mode for Swift
# compilation. Make it 'PUBLIC' to ensure it is propagated to users of the
# library.
# target_compile_options(
#   mac_inspect

#   PUBLIC "$<$<COMPILE_LANGUAGE:Swift>:-cxx-interoperability-mode=default>"
# )

# SWIG Instructions to build a python module called "mac_inspect"

# find_package(SWIG COMPONENTS python)
# include(UseSWIG)

# find_package(Python3 COMPONENTS Interpreter Development)

# include_directories(${Python3_INCLUDE_DIRS})
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# set_property(SOURCE mac_inspect.i PROPERTY CPLUSPLUS ON)

# swig_add_library(
#   # The name of the c++ library used by python module
#   mac_python_inspect
#   TYPE SHARED
#   LANGUAGE python
#   SOURCES mac_inspect.i
# )

# set_target_properties(
#   mac_python_inspect

#   PROPERTIES
#   SUFFIX .so
# )

# target_link_libraries(
#   # Target to link
#   mac_python_inspect

#   # Items to link into the target
#   mac_inspect
#   ${Python3_LIBRARIES}
# )

# set_property(
#   TARGET mac_python_inspect
#   PROPERTY
#     SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
# )

