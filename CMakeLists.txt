cmake_minimum_required(VERSION 3.9)
project(Matrici)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(matrix_run ${SOURCE_FILES})

include_directories(matrix)

add_subdirectory(matrix)
add_subdirectory(matrix_tests)

target_link_libraries(matrix_run matrix)