add_library(
  # Name
  atspi_wrapper

  # Sources
  atspi_wrapper.cc
  atspi_wrapper.h
)

add_executable(
  # Name
  dump_tree_atspi

  # Sources
  dump_tree_atspi.cc
)

# Find installed libatspi
find_library(LIB_ATSPI libatspi.so.0)

target_link_libraries(
  # Target to link (created above)
  dump_tree_atspi

  # Items to link into the target
  PRIVATE
    atspi_wrapper
    "${LIB_ATSPI}"
)
