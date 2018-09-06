project(matrix)

set(HEADER_FILES Matrix.h Factory.h)

set(SOURCE_FILES Matrix.cpp)

add_library(matrix STATIC ${SOURCE_FILES} ${HEADER_FILES})