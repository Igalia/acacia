
add_library(
  # Name
  acacia_atspi

  # This value needs to be the same as the SWIG_ADD_LIBRARY
  # And I think we want a shared library for including in python's runtime
  SHARED

  # Sources
  atspi_node.cc
  atspi_action_interface.cc
  atspi_component_interface.cc
  atspi_document_interface.cc
  atspi_hyperlink_interface.cc
  atspi_table_interface.cc
  atspi_table_cell_interface.cc
  atspi_text_interface.cc
  atspi_value_interface.cc
  linux_utils.cc
)

if (ACACIA_CAT)
  target_sources(
    acacia_atspi
    PRIVATE
    acat_context_impl.cc
    acat_node_impl.cc
  )
endif (ACACIA_CAT)

# CMake module that can find system c++ librarys
find_package(
  PkgConfig
  REQUIRED
)

pkg_check_modules(
  # Prefix for variable names set by this function
  # _INCLUDE_DIRS, _LIBRARIES and _CFLAGS_OTHER
  ATSPI2
  REQUIRED
  # Module name
  "atspi-2")

# With this, we can #include "atspi/atspi.h"
target_include_directories(
  acacia_atspi

  PUBLIC
    ${PROJECT_BINARY_DIR}/include
    ${ATSPI2_INCLUDE_DIRS}
)

target_link_libraries(
  # Target to link (created above)
  acacia_atspi

  # Items to link into the target
  PRIVATE
    "${ATSPI2_LIBRARIES}"
)

install(TARGETS
  acacia_atspi LIBRARY
)

# SWIG Instructions to build library bindings to different languages
# (only required if at least one binding is ON).

if (ACACIA_PYTHON OR ACACIA_NODEJS)
  FIND_PACKAGE(SWIG REQUIRED)
  INCLUDE(${SWIG_USE_FILE})
endif()

# Generate Python bindings using swig + python3

if (ACACIA_PYTHON)
  FIND_PACKAGE(Python3 COMPONENTS Interpreter Development.Module)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
  INCLUDE_DIRECTORIES(${Python3_INCLUDE_DIRS})

  SET_SOURCE_FILES_PROPERTIES(acacia_atspi.i PROPERTIES CPLUSPLUS ON)

  SWIG_ADD_LIBRARY(
    # The name of the c++ library used by python module
    acacia_atspi_python
    TYPE SHARED
    LANGUAGE python
    SOURCES acacia_atspi.i
  )

  TARGET_LINK_LIBRARIES(
    acacia_atspi_python
    acacia_atspi
    ${python3_LIBRARIES}
  )

  set_property(
    TARGET acacia_atspi_python
    PROPERTY
      SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
  )

  execute_process (
    COMMAND python3 -c "import sys; ver_info = sys.version_info; print(f'python{ver_info[0]}.{ver_info[1]}', end='')"
    OUTPUT_VARIABLE PY_MODULE_DIR
  )

  install(TARGETS
    acacia_atspi_python
      LIBRARY
      DESTINATION "lib/${PY_MODULE_DIR}/dist-packages"
  )
  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/acacia_atspi.py DESTINATION "lib/${PY_MODULE_DIR}/dist-packages"
  )
endif()


# Generate a NodeJS Module using swig + node-gyp

if (ACACIA_NODEJS)
  find_program(
    NODE_GYP "node-gyp"
    REQUIRED
  )

  ## Generate `binding.gyp` file for node-gyp
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/binding.gyp.in binding.gyp
  )

  ## Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT acacia_atspi_nodejs_wrap.cxx
    DEPENDS
      ${CMAKE_CURRENT_SOURCE_DIR}/acacia_atspi.i
    COMMAND
      swig -c++ -javascript -node -o acacia_atspi_nodejs_wrap.cxx -I${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/acacia_atspi.i
    VERBATIM
  )

  add_custom_command(
    OUTPUT acacia_atspi.node
    DEPENDS
      libacacia_atspi.so
      binding.gyp
      acacia_atspi_nodejs_wrap.cxx
    COMMAND
      ${NODE_GYP} configure build
      COMMAND cp "./build/Release/acacia_atspi.node" .
    VERBATIM
  )

  add_custom_target(
    acacia_atspi_module ALL
    DEPENDS
      acacia_atspi
      acacia_atspi.node
  )

  set_property(
    TARGET acacia_atspi_module
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      binding.gyp
      ${CMAKE_CURRENT_BINARY_DIR}/build
      acacia_atspi.node
  )

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/acacia_atspi.node DESTINATION "lib/node_modules"
  )
endif (ACACIA_NODEJS)
