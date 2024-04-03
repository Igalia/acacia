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

if (AXA_PYTHON_MODULE)
  add_custom_target(
    dump_tree_atspi.py
    ALL
    DEPENDS
      acacia_atspi
      acacia_atspi_python
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_atspi.py ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/_acacia_atspi_python.so ${CMAKE_CURRENT_BINARY_DIR}/_acacia_atspi_python.so
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/acacia_atspi.py ${CMAKE_CURRENT_BINARY_DIR}/acacia_atspi.py
    VERBATIM
  )
endif (AXA_PYTHON_MODULE)

if (AXA_NODEJS_MODULE)
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
endif (AXA_NODEJS_MODULE)
