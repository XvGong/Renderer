cmake_minimum_required(VERSION 2.8)

project(Renderer)

aux_source_directory(. DIR_SRCS)

add_executable(Renderer ${DIR_SRCS})