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

if (AXA_PYTHON_MODULE)
  add_custom_target(
    dump_tree_ia2.py
    ALL
    DEPENDS
      ia2_inspect
      ia2_inspect.py
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_ia2.py "${WIN_OUTPUT_DIRECTORY}/$<CONFIG>"
  )
endif (AXA_PYTHON_MODULE)
