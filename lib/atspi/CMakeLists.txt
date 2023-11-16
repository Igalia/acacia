# Feature flag for NodeJS bindings
option(
  ATSPI_NODEJS_MODULE
  "Build NodeJS bindings (requires swig and node-gyp)"
  ON
)

add_library(
  # Name
  atspi_inspect

  # This value needs to be the same as the SWIG_ADD_LIBRARY
  # And I think we want a shared library for including in python's runtime
  SHARED

  # Sources
  atspi_node.cc
  linux_utils.cc
)

# CMake module that can find system c++ librarys
find_package(
  PkgConfig
  REQUIRED
)

pkg_check_modules(
  # Prefix for variable names set by this function
  # _INCLUDE_DIRS, _LIBRARIES and _CFLAGS_OTHER
  ATSPI2
  REQUIRED
  # Module name
  "atspi-2")

# With this, we can #include "atspi/atspi.h"
target_include_directories(
  atspi_inspect

  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${ATSPI2_INCLUDE_DIRS}
)

target_link_libraries(
  # Target to link (created above)
  atspi_inspect

  # Items to link into the target
  PRIVATE
    "${ATSPI2_LIBRARIES}"
)

add_executable(
  # Name
  dump_tree_atspi

  # Sources
  dump_tree_atspi.cc
)

target_link_libraries(
  # Target to link (created above)
  dump_tree_atspi

  # Items to link into the target
  PRIVATE
    atspi_inspect
)

# SWIG Instructions to build a python module called "atspi_inspect"

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET_SOURCE_FILES_PROPERTIES(atspi_inspect.i PROPERTIES CPLUSPLUS ON)

SWIG_ADD_LIBRARY(
  # The name of the c++ library used by python module
  atspi_python_inspect
  TYPE SHARED
  LANGUAGE python
  SOURCES atspi_inspect.i
)

TARGET_LINK_LIBRARIES(
  atspi_python_inspect
  atspi_inspect
  ${PYTHON_LIBRARIES}
)

set_property(
  TARGET atspi_python_inspect
  PROPERTY
    SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
)

# Generate a NodeJS Module using swig + node-gyp

if (ATSPI_NODEJS_MODULE)
  find_program(
    NODE_GYP "node-gyp"
    REQUIRED
  )

  ## Final cmake target and proper destination for the NodeJS module
  add_custom_target(
    atspi_inspect.node ALL
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/build/Release/atspi_inspect.node"
    COMMAND cp "./build/Release/atspi_inspect.node" .
  )

  set_property(
    TARGET atspi_inspect.node
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      binding.gyp
      ${CMAKE_CURRENT_BINARY_DIR}/build
      atspi_inspect.node
  )

  ## Generate `binding.gyp` file for node-gyp
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/binding.gyp.in binding.gyp
  )

  ## Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT "atspi_nodejs_inspect_wrap.cxx"
    COMMAND swig -c++ -javascript -node -o atspi_nodejs_inspect_wrap.cxx -I${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/atspi_inspect.i
    VERBATIM
  )

  ## Generate NodeJS module
  add_custom_command(
    OUTPUT "build/Release/atspi_inspect.node"
    DEPENDS atspi_nodejs_inspect_wrap.cxx
    COMMAND ${NODE_GYP} configure build
    VERBATIM
  )
endif (ATSPI_NODEJS_MODULE)
