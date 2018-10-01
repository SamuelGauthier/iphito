find_package(OpenGL REQUIRED)

#set(TARGET_H Layer.h Canvas.h Curve.h)
#set(TARGET_SRC Layer.cpp Canvas.cpp)
include(main.cmake)

add_executable(iphito main.cpp ${TARGET_SRC} ${TARGET_H})

find_package (GLEW)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries (iphito ${GLEW_LIBRARIES})
endif (GLEW_FOUND)


find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${GLFW_LIBRARIES})

message(${CMAKE_MODULE_PATH})
find_package(Eigen3 3.3.5)
message(${EIGEN3_INCLUDE_DIR})
message("$ENV{EIGEN3_INCLUDE_DIR}")
include_directories(${EIGEN3_INCLUDE_DIR})
set(LIBS ${LIBS} ${GLFW_LIBRARIES} ${EIGEN3_INCLUDE_DIR})


target_link_libraries(iphito ${OPENGL_gl_LIBRARY})
target_link_libraries(iphito ${LIBS})
