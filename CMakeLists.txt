cmake_minimum_required(VERSION 3.16)
project(IOT LANGUAGES CXX)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Add Google Test framework
add_subdirectory(google)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Link tests for reading files
add_executable(Google_Test_readfile_run tests/test_readfile.cpp src/readfile.cpp)
target_link_libraries(Google_Test_readfile_run gtest gtest_main)
target_link_libraries(Google_Test_readfile_run gmock)

# Link tests for main
add_executable(Google_Test_polygon_run tests/test_polygon.cpp src/polygon.cpp src/readfile.cpp)
target_link_libraries(Google_Test_polygon_run gtest gtest_main)
target_link_libraries(Google_Test_polygon_run gmock)

# Include SFML via Git
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Link the IOT project
add_executable(IOT src/main.cpp
        src/polygon.cpp
        src/readfile.cpp
        src/file_manager.cpp
        src/sfml.cpp
)

# Copy OpenAL DLL for Windows
if (WIN32)
    add_custom_command(
            TARGET IOT
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:IOT>
            VERBATIM)
endif ()

# Link SFML libraries
target_link_libraries(IOT PRIVATE sfml-graphics)
# Set C++ standard to C++17
target_compile_features(IOT PRIVATE cxx_std_17)
# Install the IOT executable
install(TARGETS IOT)

# Link the IOT executable with wxWidgets libraries
set(wxWidgets_ROOT_DIR "C:/wxwidgets") # absolute location wxwidgets
set(wxWidgets_LIB_DIR "C:/wxwidgets/lib/gcc810_x64_dll")
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(IOT PRIVATE ${wxWidgets_LIBRARIES})
target_include_directories(IOT PRIVATE ${wxWidgets_INCLUDE_DIRS})
