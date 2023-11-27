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

# Set up a list called SWIFT_SOURCES which will be used by both the
# Swift-only library and the C++ header generation rule
list(APPEND SWIFT_SOURCES
  axapi_node.swift
  mac_utils.swift
)

# The C++ header generation rule requires a path relative to the project root,
# so create a copy of SWIFT_SOURCES with the current source dir prepended
# to each
list(TRANSFORM SWIFT_SOURCES
  PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/"
  OUTPUT_VARIABLE SWIFT_SOURCES_FULL_PATH
)

# Pure Swift library
add_library(
  # Name
  swift_mac_utils

  # Sources
  ${SWIFT_SOURCES}
)

# Set the Swift_MODULE_NAME property for swift_mac_utils, used below to generate
# the C++ header file.
#
# Normally it defaults to the name of the target, but we're using snake_case for
# the target name, so this gives it a more Swift-appropriate CamelCased name.
set_target_properties(swift_mac_utils
  PROPERTIES Swift_MODULE_NAME "SwiftMacUtils"
)

# Generated C++ header for the Swift library
_swift_generate_cxx_header_target(
  # Target name
  mac_utils_swift_h

  # SwiftModule/C++ namespace
  SwiftMacUtils

  # Generated header output path
  "${GENERATED_FILES_BASEPATH}/${RELATIVE_CURRENT_SOURCE_DIR}/mac_utils_swift.h"

  # Sources (keyword argument)
  SOURCES "${SWIFT_SOURCES_FULL_PATH}"
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
add_dependencies(
  # Add dependencies to target
  dump_tree_mac

  # Dependencies to add
  mac_utils_swift_h
)

# Link the pure Swift implementation of swift_mac_utils into the dump_tree_mac
# executable
target_link_libraries(
  # Target to link (created above)
  dump_tree_mac

  # Items to link into the target
  PRIVATE swift_mac_utils
)

# When building dump_tree_mac, enable C++ interoperability mode for Swift
# compilation. Make it 'PUBLIC' to ensure it is propagated to users of the
# library.
target_compile_options(swift_mac_utils
  PUBLIC "$<$<COMPILE_LANGUAGE:Swift>:-cxx-interoperability-mode=default>"
)
