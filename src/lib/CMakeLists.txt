set(TARGET_NAME gifsicle)

set(SOURCES
    clp.c
    fmalloc.c
    giffunc.c
    gifread.c
    gifunopt.c
    merge.c
    optimize.c
    quantize.c
    support.c
    xform.c
    gifsicle.c
    gifwrite.c
    progress.cpp
    utility.cpp
)

add_library(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC ${GIFSICLE_INCLUDE})
target_compile_definitions(${TARGET_NAME} PUBLIC HAVE_CONFIG_H)