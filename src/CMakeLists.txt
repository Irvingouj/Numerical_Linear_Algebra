file(GLOB matrix_SRC
     "*.c"
)

include_directories(${PROJECT_INCLUDE_DIR})
add_library(Matrix STATIC ${matrix_SRC})
target_link_libraries(Matrix m)
