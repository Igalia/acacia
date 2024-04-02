find_package(Doxygen REQUIRED)

set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(
  doc_doxygen
  ALL
  COMMAND
    ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT
    "Generating API documentation with Doxygen"
  VERBATIM
)

if (NOT AXA_LIBAXACCESS)
  set(DOXY_EXCLUDE 'axa_*')
endif ()

configure_file(
  ${DOXYGEN_IN}
  ${DOXYGEN_OUT}
  @ONLY
)

install(DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION share/doc/${CMAKE_PROJECT_NAME}
)
