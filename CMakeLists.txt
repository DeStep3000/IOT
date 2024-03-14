cmake_minimum_required(VERSION 3.27)
project(IOT)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(google)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(SFML)
include_directories(${SFML_SOURCE_DIR}/include ${SFML_SOURCE_DIR})

set(Files main.cpp readfile.cpp tests.cpp sfml.cpp)

add_executable(${PROJECT_NAME} ${Files})
add_executable(tests ${Files})

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} gtest gmock pthread)
target_link_libraries(${PROJECT_NAME} SFML audio graphics window)
