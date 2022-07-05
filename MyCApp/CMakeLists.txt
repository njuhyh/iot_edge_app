cmake_minimum_required(VERSION 3.9.5)
project(MyCApp C)

set(CMAKE_C_STANDARD 99)

link_directories(./lib)
include_directories(./include)

add_executable(MyCApp main.c)

target_link_libraries(MyCApp module curl json-c)