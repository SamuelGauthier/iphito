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

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
    catch2/2.13.1
    docopt.cpp/0.6.3 
    spdlog/1.8.0
    #
    opengl/system
    glfw/3.3.2
    glew/2.1.0
    eigen/3.3.7
    )

include(cmake/Conan.cmake)
run_conan()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src/main ../bin/main)
add_subdirectory(src/test ../bin/test)
