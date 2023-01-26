include_directories(${PROJECT_INCLUDE_DIR})
enable_testing()
add_executable(matrix_test_1 matrix_test.c)
add_test(NAME matrix_test_1 
        COMMAND matrix_test_1)