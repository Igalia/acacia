add_executable(
  dump_tree_atspi
  dump_tree_atspi.cc
)

target_link_libraries(
  dump_tree_atspi
  PRIVATE
    acacia_atspi
)

add_custom_target(
  examples
  DEPENDS
    dump_tree_atspi
)

if (ACACIA_NODEJS)
  add_custom_target(
    dump_tree_atspi.js
    ALL
    DEPENDS
      acacia_atspi
      acacia_atspi_module
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_atspi.js ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/acacia_atspi.node ${CMAKE_CURRENT_BINARY_DIR}/acacia_atspi.node
    VERBATIM
  )
endif (ACACIA_NODEJS)
