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

target_compile_definitions(
  axaccess
  PRIVATE
    # preprocessor macro to specify we are building a binary .dll, in which
    # case all AXA_EXPORTS will result in a dllexport statement.
    axaccess_EXPORTS
)

# Feature flag for Python bindings, ON by default
option(
  AXA_PYTHON_MODULE
  "Build Python bindings (requires swig and python3)"
  ON
)

# Feature flag for NodeJS bindings, ON by default
option(
  AXA_NODEJS_MODULE
  "Build NodeJS bindings (requires swig and node-gyp)"
  ON
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
    PUBLIC -DAXA_API_AXAPI
  )

  add_subdirectory(mac)
  target_link_libraries(
    axaccess
    PRIVATE
      mac_inspect
  )
endif(APPLE)

if(WIN32)
  add_subdirectory(ia2)
endif(WIN32)

target_sources(
  axaccess
  PRIVATE
    ${AXA_SOURCES}
)

target_include_directories(
  axaccess
  PUBLIC
    ${PROJECT_BINARY_DIR}/include
)
