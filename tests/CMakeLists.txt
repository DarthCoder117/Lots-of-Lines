cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(tests)

set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/3rd-party/Catch/include)
include_directories(${CMAKE_SOURCE_DIR}/DataModel/include)

# Add all files in test folder
file(GLOB sources "${PROJECT_SOURCE_DIR}/*.cpp")
add_executable(tests ${sources})
add_dependencies(tests DataModel)
target_link_libraries(tests DataModel)

add_test(tests ${PROJECT_BINARY_DIR}/bin/tests)
