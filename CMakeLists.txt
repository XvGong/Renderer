cmake_minimum_required(VERSION 3.24)

project(Renderer)

set(SOURCES
	main.cpp	
	Color.h
	Device.h
	Image.h
	Renderer.h
	RenderObject.h
)

include_directories(inc)

link_libraries(easyx)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCES})