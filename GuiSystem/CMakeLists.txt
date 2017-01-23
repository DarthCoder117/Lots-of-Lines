cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(GuiSystem)

file(GLOB headers "${PROJECT_SOURCE_DIR}/include/LotsOfLines/*.hpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/DataModel/include")
include_directories("${CMAKE_SOURCE_DIR}/RenderingSystem/include")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(GuiSystem ${sources} ${headers})
add_dependencies(GuiSystem DataModel)
add_dependencies(GuiSystem RenderingSystem)

#Include Qt
find_package(Qt5Widgets)
target_link_libraries(GuiSystem Qt5::Widgets)
