add_library(
  # Name
  ia2_inspect
  SHARED

  # Sources
  ia2_node.cc
  win_utils.cc
)

add_dependencies(
  ia2_inspect

  iaccessible2
)

target_link_libraries(
  ia2_inspect

  oleacc
  iaccessible2
)

target_compile_definitions(
  ia2_inspect
  PRIVATE
    # preprocessor macro to specify we are building a binary .dll, in which
    # case all AXA_EXPORTS will result in a dllexport statement.
    axaccess_EXPORTS
)
