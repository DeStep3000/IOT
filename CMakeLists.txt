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
add_executable(SFMLProject sfml.cpp)

target_link_libraries(SFMLProject PRIVATE sfml-graphics)
target_compile_features(SFMLProject PRIVATE cxx_std_17)

## Подключаем QT через гит(хз так проще)
#include(FetchContent)
#FetchContent_Declare(QT
#        GIT_REPOSITORY https://github.com/qt/qt5.git
#        GIT_TAG 6.7)
#FetchContent_MakeAvailable(QT)
#
## Линкуем QT проект

#
#target_link_libraries(QT_Graphic PRIVATE Qt::Widgets)
#target_compile_features(QT_Graphic PRIVATE cxx_std_17)

#set(Qt5_DIR "C:\\Qt\\Qt5.12.12\\5.12.12\\mingw73_64\\lib\\cmake")
#set(CMAKE_AUTOMOC ON)
#find_package(Qt5Widgets REQUIRED)
#
#add_executable(QT_Graphic qt_files/qt_graphic.cpp)
#target_link_libraries(QT_Graphic Qt5::Widgets)

# Линкуем тесты
# Линкуем тесты для чтения файлов
add_executable(Google_Test_readfile_run tests/test_readfile.cpp readfile.cpp)
target_link_libraries(Google_Test_readfile_run gtest gtest_main)
target_link_libraries(Google_Test_readfile_run gmock)

# Линкуем тесты для main
add_executable(Google_Test_main_run tests/test_main.cpp readfile.cpp)
target_link_libraries(Google_Test_main_run gtest gtest_main)
target_link_libraries(Google_Test_main_run gmock)

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
#install(TARGETS QT_Graphic)