# Target macOS 13 or later
# https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_DEPLOYMENT_TARGET.html
set(CMAKE_OSX_DEPLOYMENT_TARGET 13.0)

add_library(
  # Name
  mac_inspect

  # Sources
  axapi_node.mm
)

find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
cmake_print_variables(APPLICATION_SERVICES_FRAMEWORK)
find_library(FOUNDATION_FRAMEWORK Foundation)
cmake_print_variables(FOUNDATION_FRAMEWORK)

target_include_directories(
  mac_inspect

  PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  mac_inspect

  PUBLIC
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
endif()

# Generate a NodeJS Module using swig + node-gyp

if (AXA_NODEJS_MODULE)
  find_program(
    NODE_GYP "node-gyp"
    REQUIRED
  )

  # Final cmake target and proper destination for the NodeJS module
  add_custom_target(
    axapi_inspect.node ALL
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/build/Release/axapi_inspect.node"
    COMMAND cp "./build/Release/axapi_inspect.node" .
  )

  set_property(
    TARGET axapi_inspect.node
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      binding.gyp
      ${CMAKE_CURRENT_BINARY_DIR}/build
      axapi_inspect.node
  )

  # Generate `binding.gyp` file for node-gyp
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/binding.gyp.in binding.gyp
  )

  # Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT "axapi_nodejs_inspect_wrap.cxx"
    COMMAND swig -c++ -javascript -node -o axapi_nodejs_inspect_wrap.cxx -I${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/mac_inspect.i
    VERBATIM
  )

  # Generate NodeJS module
  add_custom_command(
    OUTPUT "build/Release/axapi_inspect.node"
    DEPENDS axapi_nodejs_inspect_wrap.cxx
    COMMAND ${NODE_GYP} configure build
    VERBATIM
  )
endif (AXA_NODEJS_MODULE)
