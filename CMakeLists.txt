cmake_minimum_required(VERSION 3.16)

project(gifsicle)

option(DEBUG "debug version of wasm with -g2 level" OFF)

set(CMAKE_C_COMPILER "emcc")
set(CMAKE_CXX_COMPILER "em++")

set(GIFSICLE_EMCC_FLAGS "--bind -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME=Gifsicle -O3")
if (DEBUG)
    message("Build with debug info")
    set(GIFSICLE_EMCC_FLAGS "${GIFSICLE_EMCC_FLAGS} -g2 -s ASSERTIONS=2")
endif()

add_executable(gifsicle
    src/clp.c
    src/fmalloc.c
    src/giffunc.c
    src/gifread.c
    src/gifunopt.c
    src/merge.c
    src/optimize.c
    src/quantize.c
    src/support.c
    src/xform.c
    src/gifsicle.c
    src/gifwrite.c
    src/bind.cpp
    src/coptions.cpp
)
target_compile_definitions(gifsicle PUBLIC HAVE_CONFIG_H)
target_include_directories(gifsicle PUBLIC include ./)
set_target_properties(gifsicle PROPERTIES LINK_FLAGS ${GIFSICLE_EMCC_FLAGS})
