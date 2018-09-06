include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicMatrixTests matrix_check.cpp)

target_link_libraries(runBasicMatrixTests gtest gtest_main)
target_link_libraries(runBasicMatrixTests matrix)