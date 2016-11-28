cmake_minimum_required(VERSION 3.6)
project(Iturburu_kodea)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -lm")

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES display.c io.c load_obj.c main.c matrizeak.c matrizeak.h)
add_executable(Iturburu_kodea ${SOURCE_FILES})

target_link_libraries(Iturburu_kodea ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} m)