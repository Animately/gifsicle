cmake_minimum_required(VERSION 3.16)

project(gifsicle)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CTest)
include(Doctest)
include(ExternalProject)

option(DEBUG "debug version of wasm with -g2 level" OFF)
option(ENABLE_TESTS "Enable tests" ON)

set(DEPS_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rdParty)

set(GIFSICLE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
set(GIFSICLELIB_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

add_subdirectory(src)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()
