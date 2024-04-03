add_library(
  # Name
  ia2_inspect
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
  ia2_inspect

  iaccessible2
)

target_link_libraries(
  ia2_inspect

  oleacc
  iaccessible2
)

target_compile_definitions(
  ia2_inspect
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

# Generate a python module called "ia2_inspect"

if (ACACIA_PYTHON)

  FIND_PACKAGE(Python3 COMPONENTS Interpreter Development.Module)
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
  INCLUDE_DIRECTORIES(${Python3_INCLUDE_DIRS})

  SET_SOURCE_FILES_PROPERTIES(ia2_inspect.i PROPERTIES CPLUSPLUS ON)

  SWIG_ADD_LIBRARY(
    # The name of the c++ library used by python module
    ia2_python_inspect
    TYPE SHARED
    SOURCES ia2_inspect.i
    LANGUAGE python
    OUTPUT_DIR "${WIN_OUTPUT_DIRECTORY}"
  )

  TARGET_LINK_LIBRARIES(
    ia2_python_inspect
    ia2_inspect
    ${Python3_LIBRARIES}
  )

  set_property(
    TARGET ia2_python_inspect
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
    ia2_inspect_node_module ALL
    DEPENDS
      ia2_inspect
      ia2_inspect.node
  )

  add_custom_command(
    OUTPUT ia2_inspect.node
    DEPENDS
    "${CMAKE_CURRENT_BINARY_DIR}/ia2_nodejs_inspect_wrap.cxx"
    COMMAND
      ${NODE_GYP} configure build
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "${NODE_GYP_OUTPUT_DIR}/ia2_inspect.node" "${WIN_OUTPUT_DIRECTORY}"
    VERBATIM
  )

  set_property(
    TARGET ia2_inspect_node_module
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES
      ${CMAKE_CURRENT_BINARY_DIR}/build
      ia2_inspect.node
  )

  # Generate `binding.gyp` file for node-gyp
  configure_file(
    binding.gyp.in binding.gyp
  )

  # Generate C++ wrapper for NodeJS
  add_custom_command(
    OUTPUT ia2_nodejs_inspect_wrap.cxx
    COMMAND
      swig -c++ -javascript -node -o ia2_nodejs_inspect_wrap.cxx -I${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/ia2_inspect.i
    VERBATIM
  )

  add_dependencies(
    ia2_inspect_node_module

    iaccessible2
  )

endif (ACACIA_NODEJS)
