# Target macOS 13 or later
# https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

add_library(
  # Name
  axapi_inspect

  # Sources
  axapi_node.mm
  mac_data_types.mm
  mac_helper_functions.mm
)

if (AXA_LIBAXACCESS)
  target_sources(
    axapi_inspect
    PRIVATE
      axapi_context_impl.cc
      axapi_node_impl.cc
  )
endif (AXA_LIBAXACCESS)

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
cmake_print_variables(APPLICATION_SERVICES_FRAMEWORK)
find_library(FOUNDATION_FRAMEWORK Foundation)
cmake_print_variables(FOUNDATION_FRAMEWORK)

target_include_directories(
  axapi_inspect

  PUBLIC
    ${PROJECT_BINARY_DIR}/include
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  axapi_inspect

  PRIVATE
    ${APPLICATION_SERVICES_FRAMEWORK}
    ${FOUNDATION_FRAMEWORK}
)

# SWIG Instructions to build library bindings to different languages
# (only required if at least one binding is ON).

if (AXA_PYTHON_MODULE OR AXA_NODEJS_MODULE)
  find_package(SWIG REQUIRED)
  include(UseSWIG)
endif()

# SWIG Instructions to build a python module called "axapi_inspect"

if (AXA_PYTHON_MODULE)
  find_package(Python3 COMPONENTS Interpreter Development)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  include_directories(${Python3_INCLUDE_DIRS})

  set_property(SOURCE axapi_inspect.i PROPERTY CPLUSPLUS ON)

  swig_add_library(
    # The name of the c++ library used by python module
    python_axapi_inspect
    TYPE SHARED
    LANGUAGE python
    SOURCES axapi_inspect.i
  )

  set_target_properties(
    python_axapi_inspect

    PROPERTIES
    SUFFIX .so
  )

  target_link_libraries(
    # Target to link
    python_axapi_inspect

    # Items to link into the target
    axapi_inspect
    ${Python3_LIBRARIES}
  )

  set_property(
    TARGET python_axapi_inspect
    PROPERTY
      SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
  )
endif()

# Generate a NodeJS Module using swig + node-gyp

if (AXA_NODEJS_MODULE)
  find_program(
    NODE_GYP "node-gyp"
    REQUIRED
  )

  # node-gyp will place output files in the following folder.
  set(NODE_GYP_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/build/Release")


  # Final cmake target and proper destination for the NodeJS module
  add_custom_target(
    axapi_inspect.node ALL
    DEPENDS
      "${CMAKE_CURRENT_BINARY_DIR}/nodejs_axapi_inspect_wrap.cxx"
    COMMAND
      ${NODE_GYP} configure build
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different "${NODE_GYP_OUTPUT_DIR}/axapi_inspect.node" .
    VERBATIM
  )

  set_property(
    TARGET axapi_inspect.node
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      ${CMAKE_CURRENT_BINARY_DIR}/build
      axapi_inspect.node
  )

  # Generate `binding.gyp` file for node-gyp
  configure_file(
    binding.gyp.in binding.gyp
  )

  # Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT nodejs_axapi_inspect_wrap.cxx
    DEPENDS axapi_inspect
    COMMAND
      swig -c++ -javascript -node -o nodejs_axapi_inspect_wrap.cxx -I${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/axapi_inspect.i
    VERBATIM
  )

endif (AXA_NODEJS_MODULE)
