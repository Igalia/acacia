# Backends
if (LINUX)
  add_subdirectory(atspi)
endif (LINUX)

if (APPLE)
  add_subdirectory(mac)
endif (APPLE)

if(WIN32)
  add_subdirectory(ia2)
endif(WIN32)


# Cross-platform API libaxaccess (experimental)
if (AXA_LIBAXACCESS)
  # Main library (libaxaccess.so)
  add_library(
    axaccess
    SHARED
  )

  add_dependencies(
    axaccess
    pub_headers
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
    EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/axaccess/export.h
  )
  target_compile_definitions(
    axaccess
    PRIVATE
      # preprocessor macro to specify we are building a binary .dll, in which
      # case all AXA_EXPORTS will result in a dllexport statement.
      axaccess_EXPORTS
  )

  target_sources(
    axaccess
    PRIVATE
      ${AXA_SOURCES}
  )

  if (LINUX)
    target_compile_definitions(
      axaccess
      PUBLIC -DAXA_API_ATSPI
    )
    target_link_libraries(
      axaccess
      PRIVATE
        atspi_inspect
    )
  endif (LINUX)

  if (APPLE)
    target_compile_definitions(
      axaccess
      PUBLIC -DAXA_API_AXAPI
    )
    target_link_libraries(
      axaccess
      PRIVATE
        mac_inspect
    )
  endif (APPLE)
endif (AXA_LIBAXACCESS)
