# Example C++ executable which depends on the Swift library/C++ bindings we
# defined in lib/mac
add_executable(
  # Name
  dump_tree_axapi

  # Sources
  dump_tree_axapi.cc
)

target_link_libraries(
  # Target to link (created above)
  dump_tree_axapi

  # Items to link into the target
  PRIVATE axapi_inspect
)

add_executable(
  # Name
  attribute_types

  # Sources
  attribute_types.cc
)

target_link_libraries(
  # Target to link (created above)
  attribute_types

  # Items to link into the target
  PRIVATE axapi_inspect
)

if (ACACIA_NODEJS)
  add_custom_target(
    dump_tree_axapi.js
    ALL
    DEPENDS
      axapi_inspect.node
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/dump_tree_axapi.js ${CMAKE_CURRENT_BINARY_DIR}/dump_tree_axapi.js
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/mac/axapi_inspect.node ${CMAKE_CURRENT_BINARY_DIR}/axapi_inspect.node
    VERBATIM
  )
endif (ACACIA_NODEJS)
