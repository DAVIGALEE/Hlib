cmake_minimum_required(VERSION 3.21)
project(Hlib)

set(CMAKE_CXX_STANDARD 17)

link_libraries(ws2_32 wsock32)

add_executable(Hlib main.cpp Hlib.cpp)
