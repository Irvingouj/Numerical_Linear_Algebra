# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
cmake_minimum_required(VERSION 3.16)
project(NUMERICAL_LIENAR_ALGEBRA C)
add_executable(${PROJECT_NAME} main.c)
# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Find packages go here.

# You should usually split this into folders, but this is a simple example
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
enable_testing()
add_subdirectory(src)
add_subdirectory(test)
target_link_libraries(${PROJECT_NAME} PUBLIC Matrix)

# Adding something we can run - Output name matches target name
