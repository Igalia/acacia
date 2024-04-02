# Smoke test (native)
add_executable(
  test_smoke
  test_smoke.cc
)
target_link_libraries(
  test_smoke
  PRIVATE atspi_inspect
)
add_test(
  NAME test_smoke
  COMMAND test_smoke
)

if (AXA_PYTHON_MODULE)
  add_custom_target(
    python_tests
    ALL
    DEPENDS
      atspi_inspect
      atspi_python_inspect
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_smoke.py ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/_atspi_python_inspect.so ${CMAKE_CURRENT_BINARY_DIR}/_atspi_python_inspect.so
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/atspi_inspect.py ${CMAKE_CURRENT_BINARY_DIR}/atspi_inspect.py
    VERBATIM
  )

  ## List all Python unit-tests here
  add_test(
    NAME test_smoke_py
    COMMAND python test_smoke.py
  )
endif (AXA_PYTHON_MODULE)

if (AXA_NODEJS_MODULE)
  add_custom_target(
    node_tests
    ALL
    DEPENDS
      atspi_inspect
      atspi_inspect_module
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_smoke.js ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/atspi_inspect.node ${CMAKE_CURRENT_BINARY_DIR}/atspi_inspect.node
    VERBATIM
  )

  ## List all NodeJS unit-tests here
  add_test(
    NAME test_smoke_js
    COMMAND node test_smoke.js
  )
endif (AXA_NODEJS_MODULE)
