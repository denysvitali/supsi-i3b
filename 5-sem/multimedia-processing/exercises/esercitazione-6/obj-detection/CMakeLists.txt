cmake_minimum_required(VERSION 3.12)
project(obj_detection)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

find_package(OpenCV REQUIRED)


add_executable(obj_detection main.cpp LegoBrick.cpp LegoBrick.h color.cpp color.h)
target_link_libraries(obj_detection ${OpenCV_LIBS})
