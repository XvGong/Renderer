cmake_minimum_required(VERSION 2.8)

project(Renderer)

aux_source_directory(. DIR_SRCS)

include_directories(include)
link_directories(lib)

add_executable(Renderer ${DIR_SRCS})
target_link_libraries(Renderer easyx)
