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

# Линкуем SFML проект
add_executable(SFMLProject src/sfml.cpp)

target_link_libraries(SFMLProject PRIVATE sfml-graphics)
target_compile_features(SFMLProject PRIVATE cxx_std_17)


find_package(wxWidgets REQUIRED)
add_executable(WxWidgets src/file_manager.cpp)
target_compile_features(WxWidgets PUBLIC cxx_std_17)
target_link_libraries(WxWidgets ${wxWidgets_LIBRARIES})
target_compile_definitions(WxWidgets PRIVATE ${wxWidgets_DEFINITIONS})
target_include_directories(WxWidgets PRIVATE ${wxWidgets_INCLUDE_DIRS})

# Подключаем OpenGL через гит(хз так проще)
#include(FetchContent)
#FetchContent_Declare(OpenGL
#        GIT_REPOSITORY https://github.com/JoeyDeVries/LearnOpenGL.git
#        GIT_TAG master)
#FetchContent_MakeAvailable(OpenGL)

## Линкуем OpenGL проект
#target_link_libraries(OpenGL_Graphic PRIVATE Qt::Widgets)
#target_compile_features(OpenGL_Graphic PRIVATE cxx_std_17)

# Линкуем тесты
# Линкуем тесты для чтения файлов
add_executable(Google_Test_readfile_run tests/test_readfile.cpp src/readfile.cpp)
target_link_libraries(Google_Test_readfile_run gtest gtest_main)
target_link_libraries(Google_Test_readfile_run gmock)

# Линкуем тесты для main
add_executable(Google_Test_main_run tests/test_main.cpp src/readfile.cpp)
target_link_libraries(Google_Test_main_run gtest gtest_main)
target_link_libraries(Google_Test_main_run gmock)

# Линкуем мат часть
add_executable(IOT src/main.cpp src/readfile.cpp)
if(WIN32)
    add_custom_command(
            TARGET SFMLProject
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SFMLProject>
            VERBATIM)
endif()

install(TARGETS SFMLProject)