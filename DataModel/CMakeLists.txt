cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(DataModel)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

file(GLOB headers "${PROJECT_SOURCE_DIR}/include/LotsOfLines/*.hpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(DataModel ${sources} ${headers})
