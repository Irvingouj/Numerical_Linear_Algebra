set(SOURCE_FILES 
matrix.c lab1.c vector.c
)
include_directories(${PROJECT_INCLUDE_DIR})
add_library(Matrix STATIC ${SOURCE_FILES})
target_link_libraries(Matrix m)
