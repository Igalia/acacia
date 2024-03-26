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
        axapi_inspect
    )
  endif (APPLE)
endif (AXA_LIBAXACCESS)
