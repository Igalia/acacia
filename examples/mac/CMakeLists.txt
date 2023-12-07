# Example C++ executable which depends on the Swift library/C++ bindings we
# defined in lib/mac
add_executable(
  # Name
  dump_tree_mac

  # Sources
  dump_tree_mac.cc
)

target_link_libraries(
  # Target to link (created above)
  dump_tree_mac

  # Items to link into the target
  PRIVATE mac_inspect
)