# Example C++ executable
add_executable(
  # Name
  dump_tree_ia2

  # Sources
  dump_tree_ia2.cc
)

target_link_libraries(
  # Target to link (created above)
  dump_tree_ia2

  # Items to link into the target
  PRIVATE ia2_inspect
)
