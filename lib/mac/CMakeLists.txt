# Verify that we have a new enough compiler
if("${CMAKE_Swift_COMPILER_VERSION}" VERSION_LESS 5.9)
  message(FATAL_ERROR "Bidirectional C++ Interop requires Swift 5.9 or greater. Have ${CMAKE_Swift_COMPILER_VERSION}")
endif()

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND
   NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  message(FATAL_ERROR "Project requires building with Clang. Have ${CMAKE_CXX_COMPILER_ID}")
endif()

set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# Set up swiftrt.o and runtime library search paths
include(InitializeSwift)
# cmake/modules/AddSwift.cmake provides the function for creating the Swift to
# C++ bridging header
include(AddSwift)

file(RELATIVE_PATH RELATIVE_CURRENT_SOURCE_DIR ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
include(CMakePrintHelpers)
cmake_print_variables(RELATIVE_CURRENT_SOURCE_DIR)

# Generate a C++ header from Swift sources
# This function is implemented in cmake/modules/AddSwift.cmake.
_swift_generate_cxx_header_target(
  # Target name
  mac_utils_swift_h

  # SwiftModule/C++ namespace
  SwiftMacUtils

  # generated header path
  "${GENERATED_FILES_BASEPATH}/${RELATIVE_CURRENT_SOURCE_DIR}/mac_utils_swift.h"

  SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/mac_utils.swift")

add_library(
  # Name
  mac

  # Sources
  mac_wrapper.cc
  mac_wrapper.h
)

add_library(
  # Name
  swift_mac_utils

  # Sources
  mac_utils.swift
)
set_target_properties(swift_mac_utils
                      PROPERTIES Swift_MODULE_NAME "SwiftMacUtils")

add_executable(
  # Name
  dump_tree_mac

  # Sources
  dump_tree_mac.cc
)

add_dependencies(dump_tree_mac
                 mac_utils_swift_h)

target_include_directories(dump_tree_mac
                           PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")

target_compile_options(dump_tree_mac PUBLIC
                       "$<$<COMPILE_LANGUAGE:Swift>:-cxx-interoperability-mode=default>")

target_link_libraries(
  # Target to link (created above)
  dump_tree_mac

  # Items to link into the target
  PRIVATE mac
  PRIVATE swift_mac_utils)