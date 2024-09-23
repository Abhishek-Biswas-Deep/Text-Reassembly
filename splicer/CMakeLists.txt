cmake_minimum_required(VERSION 3.18)
project(splicer C)

set(CMAKE_C_STANDARD 99)

add_executable(splicer main.c linked_list.c)
