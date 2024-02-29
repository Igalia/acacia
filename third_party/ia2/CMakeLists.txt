add_custom_target(
  ia2_headers
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include
  VERBATIM
)


add_subdirectory(lib)
