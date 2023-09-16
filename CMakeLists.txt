cmake_minimum_required(VERSION 3.23)
project(dll C)

set(CMAKE_C_STANDARD 99)

add_executable(dll main.c doubly_linked_list.c doubly_linked_list.h)
