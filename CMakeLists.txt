cmake_minimum_required(VERSION 3.27)
project(IOT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:\\qt-everywhere-src-6.6.2")

find_package(qt-everywhere-src-6.6.2 REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(IOT main.cpp
        readfile.cpp
        window.cpp
        window.h
        window.ui)
target_link_libraries(IOT qt-everywhere-src-6.6.2::Widgets)