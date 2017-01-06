cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(RenderingSystem)

file(GLOB headers "${PROJECT_SOURCE_DIR}/include/LotsOfLines/*.hpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(RenderingSystem ${sources} ${headers})
add_dependencies(RenderingSystem DataModel)
