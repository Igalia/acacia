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


# Cross-platform API libacacia (experimental)
if (AXA_LIBACACIA)
  # Main library (libacacia.so)
  add_library(
    acacia
    SHARED
  )

  set(
    AXA_SOURCES
    context.cc
    node.cc
  )

  target_compile_definitions(
    acacia
    PRIVATE
      # preprocessor macro to specify we are building a binary .dll, in which
      # case all ACACIA_EXPORTS will result in a dllexport statement.
      acacia_EXPORTS
  )

  target_sources(
    acacia
    PRIVATE
      ${AXA_SOURCES}
  )

  if (LINUX)
    target_compile_definitions(
      acacia
      PUBLIC -DAXA_API_ATSPI
    )
    target_link_libraries(
      acacia
      PRIVATE
        acacia_atspi
    )
  endif (LINUX)

  if (APPLE)
    target_compile_definitions(
      acacia
      PUBLIC -DAXA_API_AXAPI
    )
    target_link_libraries(
      acacia
      PRIVATE
        axapi_inspect
    )
  endif (APPLE)
endif (AXA_LIBACACIA)
