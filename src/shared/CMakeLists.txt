set(TARGET_NAME gifsicle_shared)

set(SOURCES
    bind.cpp
)

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC gifsiclelib)
