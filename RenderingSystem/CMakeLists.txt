cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(RenderingSystem)

# Include GLFW testing framework
include(ExternalProject)

ExternalProject_Add(
    glfw
    PREFIX ${CMAKE_SOURCE_DIR}/3rd-party/glfw
    URL "https://github.com/glfw/glfw/archive/3.2.1.tar.gz"
    URL_HASH "SHA1=bee9cd9a8b4925184070ade5bc287c5635830eb0"
    INSTALL_COMMAND ""
    CMAKE_ARGS -DGLFW_BUILD_DOCS:BOOL=OFF -DGLFW_BUILD_TESTS:BOOL=OFF -DGLFW_BUILD_EXAMPLES:BOOL=OFF
)

ExternalProject_Get_Property(glfw SOURCE_DIR)
include_directories(${SOURCE_DIR}/include)
ExternalProject_Get_Property(glfw BINARY_DIR)
link_directories(${BINARY_DIR}/src)

file(GLOB headers "${PROJECT_SOURCE_DIR}/include/LotsOfLines/*.hpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/DataModel/include")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(RenderingSystem ${sources} ${headers})
add_dependencies(RenderingSystem glfw)
add_dependencies(RenderingSystem DataModel)
target_link_libraries(RenderingSystem glfw3)
