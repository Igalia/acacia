add_executable(
  dump_tree_atspi
  dump_tree_atspi.cc
)

target_link_libraries(
  dump_tree_atspi
  PRIVATE
    atspi_inspect
)

if (AXA_NODEJS_MODULE)
  add_custom_target(
    dump_tree_atspi.js
    ALL
    DEPENDS
      atspi_inspect
      atspi_inspect_module
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_atspi.js ${CMAKE_CURRENT_BINARY_DIR}/
  )
endif (AXA_NODEJS_MODULE)
