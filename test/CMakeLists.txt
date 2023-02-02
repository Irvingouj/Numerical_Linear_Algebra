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

add_executable(lab2_test lab2_test.c)
target_link_libraries(lab2_test ${MATRIX_LIB})
add_test(NAME lab2_test 
        COMMAND lab2_test)

add_executable(gstest gstest.c)
target_link_libraries(gstest ${MATRIX_LIB})
add_test(NAME gstest 
        COMMAND gstest)

add_executable(lab2_test_ls lab2_test_ls.c)
target_link_libraries(lab2_test_ls ${MATRIX_LIB})
add_test(NAME lab2_test_ls 
        COMMAND lab2_test_ls)
        
# add qr test
add_executable(qr qr.c)
target_link_libraries(qr ${MATRIX_LIB})
add_test(NAME qr 
        COMMAND qr)

#add qr2 test
add_executable(qr2 qr2.c)
target_link_libraries(qr2 ${MATRIX_LIB})
add_test(NAME qr2 
        COMMAND qr2)