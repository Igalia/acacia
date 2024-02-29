add_library(
  iaccessible2
  STATIC
  ia2_api_all_i.c
)

target_include_directories(
  iaccessible2

  PUBLIC
    ${PROJECT_BINARY_DIR}/include/axaccess/ia2
)

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
