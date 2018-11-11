cmake_minimum_required(VERSION 3.12)
project(s3)

set(CMAKE_CXX_STANDARD 14)

LINK_DIRECTORIES(/usr/local/lib /usr/lib)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
include_directories( ${GLM_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

add_executable(s3 main.cpp point.cpp point.h)
target_link_libraries(s3 ${GLM_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} )