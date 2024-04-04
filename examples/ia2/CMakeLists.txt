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
  PRIVATE acacia_ia2
)

if (ACACIA_PYTHON)
  add_custom_target(
    dump_tree_ia2.py
    ALL
    DEPENDS
      acacia_ia2
      acacia_ia2_python
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_ia2.py "${WIN_OUTPUT_DIRECTORY}"
  )
endif (ACACIA_PYTHON)

if (ACACIA_NODEJS)
  add_custom_target(
    dump_tree_ia2.js
    ALL
    DEPENDS
      acacia_ia2
      acacia_ia2_node_module
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_ia2.js "${WIN_OUTPUT_DIRECTORY}"
  )
endif (ACACIA_NODEJS)
