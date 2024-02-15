add_executable(
  dump_tree_atspi
  dump_tree_atspi.cc
)

target_link_libraries(
  dump_tree_atspi
  PRIVATE
    atspi_inspect
)
