cmake_minimum_required(VERSION 3.16)
project(IOT LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Добавляем гугл тесты
add_subdirectory(google)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Линкуем тесты
# Линкуем тесты для чтения файлов
add_executable(Google_Test_readfile_run tests/test_readfile.cpp src/readfile.cpp)
target_link_libraries(Google_Test_readfile_run gtest gtest_main)
target_link_libraries(Google_Test_readfile_run gmock)

# Линкуем тесты для main
add_executable(Google_Test_polygon_run tests/test_polygon.cpp src/polygon.cpp src/readfile.cpp)
target_link_libraries(Google_Test_polygon_run gtest gtest_main)
target_link_libraries(Google_Test_polygon_run gmock)

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

if (WIN32)
    add_custom_command(
            TARGET SFMLProject
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SFMLProject>
            VERBATIM)
endif ()

install(TARGETS SFMLProject)

# Связываем исполняемый файл SFMLProject с библиотеками SFML
target_link_libraries(SFMLProject PRIVATE sfml-graphics)

# Линкуем ОБЩИЙ проект
add_executable(Math_part src/main.cpp
        src/polygon.cpp
        src/readfile.cpp
        src/file_manager.cpp
)

# Линкуем мат часть
add_executable(IOT src/main.cpp
        src/polygon.cpp
        src/readfile.cpp
        src/sfml.cpp
        src/file_manager.cpp
)

target_link_libraries(IOT PRIVATE sfml-graphics)
target_compile_features(IOT PRIVATE cxx_std_17)

# Связываем исполняемый файл IOT с библиотеками wxWidgets
set(wxWidgets_ROOT_DIR "C:/wxwidgets") # absolute location wxwidgets
set(wxWidgets_LIB_DIR "C:/wxwidgets/lib/gcc810_x64_dll")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

target_link_libraries(IOT PRIVATE ${wxWidgets_LIBRARIES})
target_include_directories(IOT PRIVATE ${wxWidgets_INCLUDE_DIRS})
