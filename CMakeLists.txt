cmake_minimum_required(VERSION 3.12)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithAsserts;RelWithDebInfo" CACHE
        INTERNAL "Build configs")
    message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")
    project("iphito")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# Set C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force colored output
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang
only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options (-fcolor-diagnostics)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
        add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

include(CMakePrintHelpers)

# Catch2
set(CATCH_INCLUDE_DIR src/external)
add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(GLFW3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# Eigen3
find_package(Eigen3 REQUIRED)

# spdlog
find_package(spdlog REQUIRED)

# # Bison
# find_package(bison REQUIRED)

# # Flex
# find_package(flex REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src/main ../bin/main)
add_subdirectory(src/test ../bin/test)
