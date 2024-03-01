# Backend-specific examples

if (LINUX)
  add_subdirectory(atspi)
endif (LINUX)

if(APPLE)
   add_subdirectory(mac)
endif(APPLE)

if(WIN32)
   add_subdirectory(ia2)
endif(WIN32)


# Cross-platform examples (experimental)
if (AXA_LIBAXACCESS)
  # EXAMPLE: cross-platform `dump_tree`
  add_executable(
    dump_tree
    dump_tree.cc
  )

  target_link_libraries(
    dump_tree
    PRIVATE
      axaccess
  )

  if (LINUX)
    target_link_libraries(
      dump_tree
      PRIVATE
        atspi_inspect
    )
  endif (LINUX)
endif (AXA_LIBAXACCESS)
