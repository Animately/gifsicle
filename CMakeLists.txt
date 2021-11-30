cmake_minimum_required(VERSION 3.16)

project(gifsicle)

option(DEBUG "debug version of wasm with -g2 level" OFF)

set(GIFSICLE_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GIFSICLELIB_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

add_subdirectory(src)