include(main.cmake)

add_executable(iphito main.cpp ${TARGET_SRC} ${TARGET_H})

target_link_libraries(iphito ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} glfw
                             spdlog::spdlog)

target_include_directories(iphito PRIVATE ${UTILS_DIR})
target_include_directories(iphito PRIVATE ${MATH_DIR})
target_include_directories(iphito PRIVATE ${RENDERER_DIR})
target_include_directories(iphito PRIVATE ${CMAKE_CURRENT_LIST_DIR})
