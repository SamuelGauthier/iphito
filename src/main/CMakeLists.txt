include(main.cmake)

add_executable(iphito main.cpp ${TARGET_SRC} ${TARGET_H})

target_link_libraries(iphito ${OPENGL_gl_LIBRARY} glfw)

# find_package (GLEW)
# if (GLEW_FOUND)
#     include_directories(${GLEW_INCLUDE_DIRS})
#     target_link_libraries (iphito ${GLEW_LIBRARIES})
# endif (GLEW_FOUND)

