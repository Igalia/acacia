# Main library (libaxaccess.so)
add_library(
  axaccess
  SHARED
)

set(
  AXA_SOURCES
  context.cc
  node.cc
)

## Backends
if(LINUX)
  target_compile_definitions(
    axaccess
    PUBLIC -DAXA_API_ATSPI
  )
  add_subdirectory(atspi)
  target_link_libraries(
    axaccess
    PRIVATE
      atspi_inspect
  )
endif(LINUX)

if(APPLE)
  target_compile_definitions(
    axaccess
    PUBLIC -DAXA_API_AXUI
  )

  add_subdirectory(mac)
endif(APPLE)


target_sources(
  axaccess
  PRIVATE
    ${AXA_SOURCES}
)

target_include_directories(
  axaccess
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
