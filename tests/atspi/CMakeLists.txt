# Smoke test (native)
add_executable(
  test_smoke
  test_smoke.cc
)
target_link_libraries(
  test_smoke
  PRIVATE acacia_atspi
)
add_test(
  NAME test_smoke
  COMMAND test_smoke
)

if (ACACIA_PYTHON)
  add_custom_target(
    python_tests
    ALL
    DEPENDS
      acacia_atspi
      acacia_atspi_python
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_smoke.py ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/_acacia_atspi_python.so ${CMAKE_CURRENT_BINARY_DIR}/_acacia_atspi_python.so
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/acacia_atspi.py ${CMAKE_CURRENT_BINARY_DIR}/acacia_atspi.py
    VERBATIM
  )

  ## List all Python unit-tests here
  add_test(
    NAME test_smoke_py
    COMMAND python test_smoke.py
  )
endif (ACACIA_PYTHON)

if (ACACIA_NODEJS)
  add_custom_target(
    node_tests
    ALL
    DEPENDS
      acacia_atspi
      acacia_atspi_module
    COMMAND
      ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_smoke.js ${CMAKE_CURRENT_BINARY_DIR}/
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/lib/atspi/acacia_atspi.node ${CMAKE_CURRENT_BINARY_DIR}/acacia_atspi.node
    VERBATIM
  )

  ## List all NodeJS unit-tests here
  add_test(
    NAME test_smoke_js
    COMMAND node test_smoke.js
  )
endif (ACACIA_NODEJS)
