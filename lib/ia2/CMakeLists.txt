add_library(
  # Name
  ia2_inspect
  SHARED

  # Sources
  ia2_node.cc
  win_utils.cc
)

target_include_directories(
  ia2_inspect

  PUBLIC
    ${PROJECT_BINARY_DIR}/include
)

target_compile_definitions(
  ia2_inspect
  PRIVATE
    # preprocessor macro to specify we are building a binary .dll, in which
    # case all AXA_EXPORTS will result in a dllexport statement.
    axaccess_EXPORTS
)
