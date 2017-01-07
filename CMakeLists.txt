set(PROJNAME "VS-Solution" CACHE STRING "The project name for this solution (-DPROJNAME=value).")

project(${PROJNAME})
cmake_minimum_required(VERSION 3.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable( ${PROJNAME} main.cpp
	src/DebugTools.cpp src/DebugTools.h
	src/glContext.cpp src/glContext.h
	src/glProgram.cpp src/glProgram.h
	src/AssetManager.cpp src/AssetManager.h
	src/ProgramInstance.cpp src/ProgramInstance.h
	src/Renderer.cpp src/Renderer.h 
	src/Camera.cpp src/Camera.h
	src/DrawableBase.cpp src/DrawableBase.h 
	src/DataSet.cpp src/DataSet.h
	src/Histogram2D.cpp src/Histogram2D.h 
	src/Trajectory.cpp src/Trajectory.h
	src/Heatmap.cpp src/Heatmap.h
	src/VisualHelper.cpp src/VisualHelper.h )

target_link_libraries(${PROJNAME} ${CONAN_LIBS})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJNAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJNAME})