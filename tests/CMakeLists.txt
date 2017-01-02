cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Include Google C++ test framework
include (ExternalProject)

ExternalProject_Add(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    PREFIX ${CMAKE_SOURCE_DIR}/3rd-party/gtest
    BUILD_COMMAND cmake
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

message(STATUS ${source_dir})

# All source files in this directory will be built as tests
file(GLOB src
    "*.cpp"
)

add_executable(tests ${src})
#target_link_libraries(tests gtest)
#add_dependencies(tests gtest)