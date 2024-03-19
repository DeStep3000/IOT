cmake_minimum_required(VERSION 3.16)
project(IOT LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Добавляем гугл тесты
add_subdirectory(google)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Подключаем SFML через гит(хз так проще)
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Линкуем SFML файл
add_executable(SFMLProject sfml.cpp)

target_link_libraries(SFMLProject PRIVATE sfml-graphics)
target_compile_features(SFMLProject PRIVATE cxx_std_17)

# Линкуем тесты
add_executable(Google_Tests_run tests.cpp readfile.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run gmock)

# Линкуем мат часть
add_executable(IOT main.cpp readfile.cpp)
if(WIN32)
    add_custom_command(
            TARGET SFMLProject
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SFMLProject>
            VERBATIM)
endif()

install(TARGETS SFMLProject)