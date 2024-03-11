add_library(
  # Name
  ia2_inspect
  SHARED

  # Sources
  ia_2.cc
  ia_action.cc
  ia_component.cc
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
    # case all AXA_EXPORTS will result in a dllexport statement.
    axaccess_EXPORTS
)

if (AXA_PYTHON_MODULE)

  # SWIG Instructions to build library bindings to different languages
  # (only required if at least one binding is ON).

  FIND_PACKAGE(SWIG REQUIRED)
  INCLUDE(${SWIG_USE_FILE})

  # Generate Python bindings using swig + python3

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
    # The "$<CONFIG> assumes we are using the Visual Studio generator
    # which puts the built files in a Release or Debug folder.
    OUTPUT_DIR "${WIN_OUTPUT_DIRECTORY}/$<CONFIG>"
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

endif(AXA_PYTHON_MODULE)
