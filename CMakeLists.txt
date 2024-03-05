cmake_minimum_required(VERSION 3.27)
project(IOT)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(IOT main.cpp
        readfile.cpp
        tests.cpp)
target_link_libraries(IOT gtest gtest_main)
target_link_libraries(IOT gtest gmock pthread)