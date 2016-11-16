set(PROJNAME "VS-Solution" CACHE STRING "The project name for this solution (-DPROJNAME=value).")

project(${PROJNAME})
cmake_minimum_required(VERSION 3.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJNAME} main.cpp
	src/SDL_Instance.cpp src/SDL_Instance.h 
	src/DebugTools.cpp src/DebugTools.h)
target_link_libraries(${PROJNAME} ${CONAN_LIBS})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJNAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJNAME})