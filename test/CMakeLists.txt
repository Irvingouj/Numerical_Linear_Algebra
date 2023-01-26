include_directories(${PROJECT_INCLUDE_DIR})
add_executable(matrix_test_1 matrix_test.c)
add_test(NAME matrix_test_1 
        COMMAND matrix_test_1)


# 2. Add a test that uses the matrix library
add_executable(matrix_multiply_test matrix_multiply_test.c)
target_link_libraries(matrix_multiply_test ${MATRIX_LIB})
message(STATUS "MATRIX_LIB: ${MATRIX_LIB}")
add_test(NAME matrix_multiply_test 
        COMMAND matrix_multiply_test)