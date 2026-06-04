cmake_minimum_required(VERSION 3.20)
project(a1)

set(CMAKE_CXX_STANDARD 17)

add_executable(bots bots.cpp)

target_link_libraries(bots pthread)