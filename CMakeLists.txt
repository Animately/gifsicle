cmake_minimum_required(VERSION 3.16)

project(gifsicle)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(CTest)
include(Doctest)
include(ExternalProject)

option(DEBUG "debug version of wasm with -g2 level" OFF)
option(ENABLE_TESTS "Enable tests" ON)

set(DEPS_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rdParty)

ExternalProject_Add(
    flatbuffers_project
    GIT_REPOSITORY "https://github.com/google/flatbuffers"
    GIT_TAG "v23.5.26"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
        -DFLATBUFFERS_BUILD_TESTS=OFF
    TEST_COMMAND ""
)

set(GIFSICLE_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GIFSICLELIB_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

add_subdirectory(src)

if (ENABLE_TESTS)
    add_subdirectory(tests)
endif()
