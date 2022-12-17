cmake_minimum_required(VERSION 3.24)
project(finalisa)

set(CMAKE_CXX_STANDARD 17)

add_executable(finalisa main.cpp)
#add ws2_32 library
target_link_libraries(finalisa ws2_32)