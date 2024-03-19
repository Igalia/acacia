# Target macOS 13 or later
# https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

add_library(
  # Name
  mac_inspect

  # Sources
  axapi_node.mm
)

if (AXA_LIBAXACCESS)
  target_sources(
    axapi_inspect
    PRIVATE
      axa_context_impl.cc
      axa_node_impl.cc
  )
endif (AXA_LIBAXACCESS)

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
cmake_print_variables(APPLICATION_SERVICES_FRAMEWORK)
find_library(FOUNDATION_FRAMEWORK Foundation)
cmake_print_variables(FOUNDATION_FRAMEWORK)

target_include_directories(
  mac_inspect

  PUBLIC
    ${PROJECT_BINARY_DIR}/include
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  mac_inspect

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

# SWIG Instructions to build a python module called "mac_inspect"

if (AXA_PYTHON_MODULE)
  find_package(Python3 COMPONENTS Interpreter Development)

  include_directories(${CMAKE_CURRENT_SOURCE_DIR})
  include_directories(${Python3_INCLUDE_DIRS})

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
    mac_inspect.node ALL
    DEPENDS
      "${CMAKE_CURRENT_BINARY_DIR}/mac_nodejs_inspect_wrap.cxx"
    COMMAND
      ${NODE_GYP} configure build
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different "${NODE_GYP_OUTPUT_DIR}/mac_inspect.node" .
    VERBATIM
  )

  set_property(
    TARGET mac_inspect.node
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      ${CMAKE_CURRENT_BINARY_DIR}/build
      mac_inspect.node
  )

  # Generate `binding.gyp` file for node-gyp
  configure_file(
    binding.gyp.in binding.gyp
  )

  # Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT mac_nodejs_inspect_wrap.cxx
    DEPENDS mac_inspect
    COMMAND
      swig -c++ -javascript -node -o mac_nodejs_inspect_wrap.cxx -I${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/mac_inspect.i
    VERBATIM
  )

endif (AXA_NODEJS_MODULE)
