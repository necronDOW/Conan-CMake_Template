project(Conan-CMake_Template)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Conan-CMake_Template main.cpp)
target_link_libraries(Conan-CMake_Template ${CONAN_LIBS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "Conan-CMake_Template")