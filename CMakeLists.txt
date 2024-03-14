cmake_minimum_required(VERSION 3.27)
project(IOT)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(Files main.cpp readfile.cpp tests.cpp)

add_executable(${PROJECT_NAME} ${Files})

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} gtest gmock pthread)