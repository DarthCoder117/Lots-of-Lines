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

#Include GLEW for Windows development
ExternalProject_Add(
    glew
    PREFIX ${CMAKE_SOURCE_DIR}/3rd-party/glew
    URL "http://downloads.sourceforge.net/project/glew/glew/2.0.0/glew-2.0.0-win32.zip?r=http%3A%2F%2Fglew.sourceforge.net%2F&ts=1484093054&use_mirror=cytranet"
    INSTALL_COMMAND ""
    BUILD_COMMAND ""
    CONFIGURE_COMMAND ""
)

#Add paths for GLFW
ExternalProject_Get_Property(glfw SOURCE_DIR)
include_directories(${SOURCE_DIR}/include)
ExternalProject_Get_Property(glfw BINARY_DIR)
link_directories(${BINARY_DIR}/src)

#Add paths for GLEW
ExternalProject_Get_Property(glew SOURCE_DIR)
include_directories(${SOURCE_DIR}/include)
link_directories(${SOURCE_DIR}/lib/Release/Win32)

file(GLOB headers "${PROJECT_SOURCE_DIR}/include/LotsOfLines/*.hpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/DataModel/include")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(RenderingSystem ${sources} ${headers})
add_dependencies(RenderingSystem glew)
add_dependencies(RenderingSystem glfw)
add_dependencies(RenderingSystem DataModel)

include(FindOpenGL)
find_package(OpenGL)

target_link_libraries(RenderingSystem glew32 glfw3 ${OPENGL_gl_LIBRARY})
