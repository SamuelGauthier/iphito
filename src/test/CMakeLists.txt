#set(TEST_TARGET_H )

include(../main/main.cmake)

set(TEST_TARGET_SRC
    Test_Layer.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/src/main)
set(MAIN_H ${TARGET_H})
set(MAIN_SRC ${TARGET_SRC})
set(MAIN_DIR ../main/)

list(TRANSFORM MAIN_H PREPEND ${MAIN_DIR})
list(TRANSFORM MAIN_SRC PREPEND ${MAIN_DIR})

add_executable(test Test_main.cpp ${TEST_TARGET_SRC} ${MAIN_H} ${MAIN_SRC})
target_link_libraries(test Catch2)
