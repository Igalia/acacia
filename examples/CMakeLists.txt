# EXAMPLE: dump_tree
add_executable(
  dump_tree
  dump_tree.cc
)

target_include_directories(
  dump_tree
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
  dump_tree
  PRIVATE
    axaccess
)

if(LINUX)
target_link_libraries(
  dump_tree
  PRIVATE
    atspi_inspect
)
endif(LINUX)


if(APPLE)
   add_subdirectory(mac)
endif(APPLE)


if(WIN32)
   add_subdirectory(ia2)
endif(WIN32)
