add_library(
  # Name
  atspi

  # Sources
  atspi.cc
  atspi.h
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
  PRIVATE atspi)