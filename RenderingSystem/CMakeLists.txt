cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(RenderingSystem)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

#Add paths for GLFW
include_directories(${CMAKE_SOURCE_DIR}/3rd-party/glfw/include)
link_directories(${CMAKE_SOURCE_DIR}/3rd-party/glfw/lib-vc2015)

#Add paths for GLM
include_directories(${CMAKE_SOURCE_DIR}/3rd-party/glm)

#Add paths for GLEW
include_directories(${CMAKE_SOURCE_DIR}/3rd-party/glew/include)
link_directories(${CMAKE_SOURCE_DIR}/3rd-party/glew/lib/Release/Win32)

file(GLOB headers "${PROJECT_SOURCE_DIR}/include/LotsOfLines/*.hpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/DataModel/include")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(RenderingSystem ${sources} ${headers})
add_dependencies(RenderingSystem DataModel)

include(FindOpenGL)
find_package(OpenGL)

target_link_libraries(RenderingSystem DataModel glew32 glfw3 ${OPENGL_gl_LIBRARY})
