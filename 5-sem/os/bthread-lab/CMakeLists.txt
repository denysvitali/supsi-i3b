cmake_minimum_required(VERSION 3.12)
project(bthread_lab C)

set(CMAKE_C_STANDARD 11)
add_executable(bthread_lab main.c)

project(example-1)
add_executable(example-1 example-1/ex1.c)

project(example-2)
add_executable(example-2 example-2/main.c)

project(example-3)
add_executable(example-3 example-3/main.c)

project(example-4)
add_executable(example-4 example-4/main.c)

project(example-5)
add_executable(example-5 example-5/main.c)