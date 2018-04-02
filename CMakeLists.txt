cmake_minimum_required(VERSION 3.9)
project(map_gfs C)

set(CMAKE_C_STANDARD 99)

add_executable(map_gfs main.c stack.c stack.h node.c node.h stack1D.c stack1D.h file.c file.h menu.c menu.h)