file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/include 
  DESTINATION ${PROJECT_BINARY_DIR}
)

add_subdirectory(lib)
