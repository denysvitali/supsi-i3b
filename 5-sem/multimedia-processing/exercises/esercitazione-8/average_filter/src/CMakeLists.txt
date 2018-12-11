cmake_minimum_required(VERSION 3.12)
project(esercitazione_8)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 14)

enable_language(CUDA)

include_directories(utilities)
include_directories(helperfunctions)
include_directories(/opt/cuda/include)

add_library(average_gpu average_gpu.cu)
set_property(TARGET average_gpu
        PROPERTY CUDA_SEPARABLE_COMPILATION ON)

add_executable(esercitazione_8
        utilities/profiling.c
        average_cpu.c
        main.cpp)

target_link_libraries(esercitazione_8 PRIVATE average_gpu)