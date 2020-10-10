include(main.cmake)

add_executable(${PROJECT_NAME}
    main.cpp
    ${TARGET_SRC}
    ${TARGET_H}
)

target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::catch2
    CONAN_PKG::docopt.cpp
    CONAN_PKG::spdlog
    CONAN_PKG::opengl
    CONAN_PKG::glfw
    CONAN_PKG::glew
    CONAN_PKG::eigen
)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    ${UTILS_DIR}
    ${MATH_DIR}
    ${RENDERER_DIR}
    ${CLI_DIR}
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
