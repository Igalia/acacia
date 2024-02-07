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

# Generate AXA_EXPORT and AXA_NO_EXPORT axa_exported.h necessary for
# including dllexport and dllimport statements in .dll source code.
include(GenerateExportHeader)
generate_export_header(
  axaccess
  BASE_NAME axa
  EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/exports/axa_export.h
)
target_compile_definitions(
  axaccess
  PRIVATE
    # preprocessor macro to specify we are building a binary .dll, in which
    # case all AXA_EXPORTS will result in a dllexport statement.
    axaccess_EXPORTS
)
include_directories(${PROJECT_BINARY_DIR}/exports)


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
    PUBLIC -DAXA_API_AXUI
  )

  add_subdirectory(mac)
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
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/exports  # axa_export.h
)
