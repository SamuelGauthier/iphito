include(main.cmake)

add_executable(iphito main.cpp ${TARGET_SRC} ${TARGET_H})

target_link_libraries(iphito ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} glfw)
