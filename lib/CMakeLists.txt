if(LINUX)
  add_subdirectory(atspi)
endif(LINUX)

if(APPLE)
  add_subdirectory(mac)
endif(APPLE)
