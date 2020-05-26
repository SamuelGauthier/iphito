include(../main/main.cmake)

set(TEST_PROJECT_NAME test)

set(TEST_TARGET_SRC
    LayerTest.cpp
    CanvasTest.cpp
    Hermite3Test.cpp
    Hermite5Test.cpp
    BezierTest.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src/main)
set(MAIN_H ${TARGET_H})
set(MAIN_SRC ${TARGET_SRC})
set(MAIN_DIR ../main/)

list(TRANSFORM MAIN_H PREPEND ${MAIN_DIR})
list(TRANSFORM MAIN_SRC PREPEND ${MAIN_DIR})

add_executable(${TEST_PROJECT_NAME}
    mainTest.cpp
    ${TEST_TARGET_SRC}
    ${MAIN_H}
    ${MAIN_SRC}
    )

target_link_libraries(${TEST_PROJECT_NAME}
    Catch2
    OpenGL::GL
    GLEW::GLEW
    glfw
    spdlog::spdlog
    )

target_include_directories(${TEST_PROJECT_NAME} PRIVATE
    ${MAIN_DIR}${UTILS_DIR}
    ${MAIN_DIR}${MATH_DIR}
    ${MAIN_DIR}${RENDERER_DIR}
    ${MAIN_DIR}${CLI_DIR}
    )
