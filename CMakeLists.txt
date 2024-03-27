cmake_minimum_required(VERSION 3.23)
project(IOT)

set(CMAKE_CXX_STANDARD 17)

add_executable(IOT main.cpp
        readfile.cpp readfile.h polygon.cpp polygon.h)
