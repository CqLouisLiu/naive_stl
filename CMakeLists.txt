cmake_minimum_required(VERSION 3.5)
project(naive_stl)

set(CMAKE_CXX_STANDARD 11)
#set()

#aux_source_directory(include/exception exception_header)
#aux_source_directory(include/internal internal_header)
#aux_source_directory(include/io io_header)
#aux_source_directory(include/net/socket socket_header)
#aux_source_directory(include/thread thread_header)
#aux_source_directory(include/util util_header)

include_directories(include)

aux_source_directory(src src_lists)

add_executable(naive main.cpp ${exception_header} ${internal_header} ${io_header} ${socket_header} ${thread_header} ${util_header} ${src_lists})