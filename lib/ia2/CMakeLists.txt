add_library(
  # Name
  acacia_ia2
  SHARED

  # Sources
  ia_2.cc
  ia_action.cc
  ia_component.cc
  ia_hyperlink.cc
  ia_node.cc
  ia_table2.cc
  ia_table_cell.cc
  ia_text.cc
  ia_value.cc
  win_utils.cc
)

add_dependencies(
  acacia_ia2

  iaccessible2
)

target_link_libraries(
  acacia_ia2

  oleacc
  iaccessible2
)

target_compile_definitions(
  acacia_ia2
  PRIVATE
    # preprocessor macro to specify we are building a binary .dll, in which
    # case all ACACIA_EXPORTS will result in a dllexport statement.
    acacia_EXPORTS
)


# SWIG Instructions to build library bindings to different languages
# (only required if at least one binding is ON).

if (ACACIA_PYTHON OR ACACIA_NODEJS)
  find_package(SWIG REQUIRED)
  include(UseSWIG)
endif()

# Generate a python module called "acacia_ia2"

if (ACACIA_PYTHON)

  FIND_PACKAGE(Python3 COMPONENTS Interpreter Development.Module)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
  INCLUDE_DIRECTORIES(${Python3_INCLUDE_DIRS})

  SET_SOURCE_FILES_PROPERTIES(acacia_ia2.i PROPERTIES CPLUSPLUS ON)

  SWIG_ADD_LIBRARY(
    # The name of the c++ library used by python module
    acacia_ia2_python
    TYPE SHARED
    SOURCES acacia_ia2.i
    LANGUAGE python
    OUTPUT_DIR "${WIN_OUTPUT_DIRECTORY}"
    # Output for the generated C++ wrapper
    OUTFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}"
  )

  TARGET_LINK_LIBRARIES(
    acacia_ia2_python
    acacia_ia2
    ${Python3_LIBRARIES}
  )

  set_property(
    TARGET acacia_ia2_python
    PROPERTY
      SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE
  )

endif(ACACIA_PYTHON)

# Generate a NodeJS Module using swig + node-gyp

if (ACACIA_NODEJS)
  find_program(
    NODE_GYP "node-gyp"
    REQUIRED
  )

  # node-gyp will place output files in the following folder.
  set(NODE_GYP_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/build/Release")

  add_custom_target(
    acacia_ia2_node_module ALL
    DEPENDS
      acacia_ia2
      acacia_ia2.node
  )

  add_custom_command(
    TARGET acacia_ia2_node_module
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy "${NODE_GYP_OUTPUT_DIR}/acacia_ia2.node" "${WIN_OUTPUT_DIRECTORY}"
  )

  add_custom_command(
    OUTPUT acacia_ia2.node
    DEPENDS
    "${CMAKE_CURRENT_BINARY_DIR}/acacia_ia2_nodejs_wrap.cxx"
    COMMAND
      ${NODE_GYP} configure build
  )

  set_property(
    TARGET acacia_ia2_node_module
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      ${CMAKE_CURRENT_BINARY_DIR}/build
      acacia_ia2.node
  )

  # Generate `binding.gyp` file for node-gyp
  configure_file(
    binding.gyp.in binding.gyp
  )

  # Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT acacia_ia2_nodejs_wrap.cxx
    COMMAND
      swig -c++ -javascript -node -o acacia_ia2_nodejs_wrap.cxx -I${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/acacia_ia2.i
    VERBATIM
  )

  add_dependencies(
    acacia_ia2_node_module

    iaccessible2
  )

endif (ACACIA_NODEJS)
