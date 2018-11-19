include(../main/main.cmake)

set(TEST_TARGET_SRC
    LayerTest.cpp
    CanvasTest.cpp
    Hermite3Test.cpp
    Hermite5Test.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src/main)
set(MAIN_H ${TARGET_H})
set(MAIN_SRC ${TARGET_SRC})
set(MAIN_DIR ../main/)

list(TRANSFORM MAIN_H PREPEND ${MAIN_DIR})
list(TRANSFORM MAIN_SRC PREPEND ${MAIN_DIR})

add_executable(test mainTest.cpp ${TEST_TARGET_SRC} ${MAIN_H} ${MAIN_SRC})
target_link_libraries(test Catch2  ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} glfw
                      spdlog::spdlog)
