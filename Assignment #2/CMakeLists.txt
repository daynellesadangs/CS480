cmake_minimum_required(VERSION 3.31)
project(a2)

set(CMAKE_CXX_STANDARD 17)

add_executable(a2 main.cpp
        command.cpp
        xsh.h
        exec.cpp)
