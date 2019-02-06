cmake_minimum_required(VERSION 3.13)
project(s9)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

include_directories(s9 ${OPENCV_INCLUDE_DIR})

add_executable(s9 main.cpp Tracker.cpp Tracker.h)
target_link_libraries(s9 ${OpenCV_LIBS})