add_library(
  # Name
  atspi_wrapper

  # Sources
  atspi_wrapper.cc
  atspi_wrapper.h
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
  atspi_wrapper

  PUBLIC
    ${ATSPI2_INCLUDE_DIRS}
)

target_link_libraries(
  # Target to link (created above)
  atspi_wrapper

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
    atspi_wrapper
)
