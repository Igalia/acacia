add_library(
  # Name
  atspi_inspect

  # This value needs to be the same as the SWIG_ADD_LIBRARY
  # And I think we want a shared library for including in python's runtime
  SHARED

  # Sources
  atspi_node.cc
  atspi_node.h
  linux_utils.cc
  linux_utils.h
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

