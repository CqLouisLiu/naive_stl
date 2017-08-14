cmake_minimum_required(VERSION 3.5)
project(naive_stl)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src bin)
add_subdirectory(src/net)
add_subdirectory(src/util)