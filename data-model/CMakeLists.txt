cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

file(GLOB src
    "./include/*.h"
    "./source/*.cpp"
)

add_library(data-model ${src})