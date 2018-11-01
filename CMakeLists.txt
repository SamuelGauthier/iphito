cmake_minimum_required(VERSION 3.12)

project("Iphito")

# Set C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src/main ../bin/main)
add_subdirectory(src/test ../bin/test)

# Catch2
set(CATCH_INCLUDE_DIR src/external)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW
find_package(GLFW3 REQUIRED)

# Eigen3
find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)
