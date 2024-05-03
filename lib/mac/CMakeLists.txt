# Target macOS 13 or later
# https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

add_library(
  # Name
  acacia_axapi

  # Sources
  axapi_node.mm
  mac_data_types.mm
  mac_helper_functions.mm
)

if (ACACIA_CAT)
  target_sources(
    acacia_axapi
    PRIVATE
      axapi_context_impl.cc
      axapi_node_impl.cc
  )
endif (ACACIA_CAT)

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
cmake_print_variables(APPLICATION_SERVICES_FRAMEWORK)
find_library(FOUNDATION_FRAMEWORK Foundation)
cmake_print_variables(FOUNDATION_FRAMEWORK)
find_library(APPKIT_FRAMEWORK AppKit)
cmake_print_variables(APPKIT_FRAMEWORK)

target_include_directories(
  acacia_axapi

  PUBLIC
    ${PROJECT_BINARY_DIR}/include
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  acacia_axapi

  PRIVATE
    ${APPLICATION_SERVICES_FRAMEWORK}
    ${FOUNDATION_FRAMEWORK}
    ${APPKIT_FRAMEWORK}
)

install(TARGETS
  acacia_axapi LIBRARY
)

# SWIG Instructions to build library bindings to different languages
# (only required if at least one binding is ON).

if (ACACIA_PYTHON OR ACACIA_NODEJS)
  find_package(SWIG REQUIRED)
  include(UseSWIG)
endif()

# Build and install a python module called "acacia_axapi" using setuptools

if (ACACIA_PYTHON)
  configure_file(setup.py.in setup.py)

  add_custom_target(
    python_acacia_axapi ALL
    DEPENDS
      acacia_axapi
      setup.py
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/acacia_axapi.i ${CMAKE_CURRENT_BINARY_DIR}/acacia_axapi.i
    COMMAND
      MACOSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET} python3 -m build
  )

  set_property(
    TARGET python_acacia_axapi
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      ${CMAKE_CURRENT_BINARY_DIR}/__pycache__
      ${CMAKE_CURRENT_BINARY_DIR}/acacia_axapi.egg-info
      ${CMAKE_CURRENT_BINARY_DIR}/dist
      ${CMAKE_CURRENT_BINARY_DIR}/acacia_axapi.i
      ${CMAKE_CURRENT_BINARY_DIR}/acacia_axapi.py
      ${CMAKE_CURRENT_BINARY_DIR}/acacia_axapi_wrap.cpp
  )

  add_custom_target(
    python_acacia_axapi_install ALL
    DEPENDS
      python_acacia_axapi
    COMMAND
      pip3 uninstall -y acacia_axapi
    COMMAND
      pip3 install --no-index -f dist acacia_axapi
  )
endif()

# Generate a NodeJS Module using swig + node-gyp

if (ACACIA_NODEJS)
  find_program(
    NODE_GYP "node-gyp"
    REQUIRED
  )

  # node-gyp will place output files in the following folder.
  set(NODE_GYP_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/build/Release")


  # Final cmake target and proper destination for the NodeJS module
  add_custom_target(
    acacia_axapi.node ALL
    DEPENDS
      "${CMAKE_CURRENT_BINARY_DIR}/nodejs_acacia_axapi_wrap.cxx"
    COMMAND
      ${NODE_GYP} configure build
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different "${NODE_GYP_OUTPUT_DIR}/acacia_axapi.node" .
    VERBATIM
  )

  set_property(
    TARGET acacia_axapi.node
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      ${CMAKE_CURRENT_BINARY_DIR}/build
      acacia_axapi.node
  )

  # Generate `binding.gyp` file for node-gyp
  configure_file(
    binding.gyp.in binding.gyp
  )

  # Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT nodejs_acacia_axapi_wrap.cxx
    DEPENDS acacia_axapi
    COMMAND
      swig -c++ -javascript -node -o nodejs_acacia_axapi_wrap.cxx -I${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/acacia_axapi.i
    VERBATIM
  )

endif (ACACIA_NODEJS)
