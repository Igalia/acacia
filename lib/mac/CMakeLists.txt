# Swift/C++ CMake configuration based heavily on
# https://github.com/mac/swift-cmake-examples/blob/main/3_bidirectional_cxx_interop/

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
  axapi_node.swift
  mac_utils.swift
)

# The C++ header generation rule requires a path relative to the project root,
# so create a copy of MAC_INSPECT_SOURCES with the current source dir prepended
# to each
list(TRANSFORM MAC_INSPECT_SOURCES
  PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/"
  OUTPUT_VARIABLE MAC_INSPECT_SOURCES_FULL_PATH
)

# Generated C++ header for the Swift library
_swift_generate_cxx_header_target(
  # Target name
  mac_inspect_swift_h

  # SwiftModule/C++ namespace
  MacInspect

  # Generated header output path
  "${GENERATED_FILES_BASEPATH}/include/axaccess/mac/mac_inspect.h"

  # Sources (keyword argument)
  SOURCES "${MAC_INSPECT_SOURCES_FULL_PATH}"
)

add_library(
  # Name
  mac_inspect

  # Sources
  ${MAC_INSPECT_SOURCES}
)

add_dependencies(
  # Add dependencies to target
  mac_inspect

  # Dependencies to add
  mac_inspect_swift_h
)

# Make sure SWIG (and other users of the mac_inspect library) can find the
# generated header file
target_include_directories(
  mac_inspect

  PUBLIC
    "${GENERATED_FILES_BASEPATH}/include"
)

# When building mac_inspect, enable C++ interoperability mode for Swift
# compilation. Make it 'PUBLIC' to ensure it is propagated to users of the
# library.
target_compile_options(
  mac_inspect

  PUBLIC "$<$<COMPILE_LANGUAGE:Swift>:-cxx-interoperability-mode=default>"
)

# Example C++ executable which depends on the Swift library/C++ bindings we
# defined above
add_executable(
  # Name
  dump_tree_mac

  # Sources
  dump_tree_mac.cc
)

# dump_tree_mac depends on the C++ header generated above
# add_dependencies(
#   # Add dependencies to target
#   dump_tree_mac

#   # Dependencies to add
#   mac_inspect_swift_h
# )

# Link the pure Swift implementation of swift_mac_utils into the dump_tree_mac
# executable
target_link_libraries(
  # Target to link (created above)
  dump_tree_mac

  # Items to link into the target
  PRIVATE mac_inspect
)

# When building dump_tree_mac, enable C++ interoperability mode for Swift
# compilation. Make it 'PUBLIC' to ensure it is propagated to users of the
# library. (Obviously this is not a library, but just as an example.)
target_compile_options(dump_tree_mac
  PUBLIC "$<$<COMPILE_LANGUAGE:Swift>:-cxx-interoperability-mode=default>"
)

# SWIG Instructions to build a python module called "mac_inspect"

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(Python3 COMPONENTS Development)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET_SOURCE_FILES_PROPERTIES(mac_inspect.i PROPERTIES CPLUSPLUS ON)

SWIG_ADD_LIBRARY(
  # The name of the c++ library used by python module
  mac_python_inspect
  TYPE SHARED
  LANGUAGE python
  SOURCES mac_inspect.i
)

TARGET_LINK_LIBRARIES(
  mac_python_inspect
  mac_inspect
  ${Python3_LIBRARIES}
)

set_property(
  TARGET mac_python_inspect
  PROPERTY
    SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
)

