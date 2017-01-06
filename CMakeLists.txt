cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(lots-of-lines)

# Visual Studio flags
if (MSVC)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMTD")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
endif(MSVC)

# Setup output directories for all targets
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add each module as a subdirectory
add_subdirectory("${CMAKE_SOURCE_DIR}/DataModel")
add_subdirectory("${CMAKE_SOURCE_DIR}/RenderingSystem")
add_subdirectory("${CMAKE_SOURCE_DIR}/tests")