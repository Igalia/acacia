add_executable(
  dump_tree_atspi
  dump_tree_atspi.cc
)

target_link_libraries(
  dump_tree_atspi
  PRIVATE
    atspi_inspect
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
      atspi_inspect
      atspi_python_inspect
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_atspi.py ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/_atspi_python_inspect.so ${CMAKE_CURRENT_BINARY_DIR}/_atspi_python_inspect.so
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/atspi_inspect.py ${CMAKE_CURRENT_BINARY_DIR}/atspi_inspect.py
    VERBATIM
  )
endif (AXA_PYTHON_MODULE)

if (AXA_NODEJS_MODULE)
  add_custom_target(
    dump_tree_atspi.js
    ALL
    DEPENDS
      atspi_inspect
      atspi_inspect_module
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_atspi.js ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/atspi_inspect.node ${CMAKE_CURRENT_BINARY_DIR}/atspi_inspect.node
    VERBATIM
  )
endif (AXA_NODEJS_MODULE)
