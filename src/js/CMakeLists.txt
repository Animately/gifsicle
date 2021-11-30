set(TARGET_NAME animately_gif)

set(SOURCES
    bind.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})

if(EMSCRIPTEN)
    set(GIFSICLE_EMCC_FLAGS "--bind -s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME=Gifsicle -O3")
    if (DEBUG)
        set(GIFSICLE_EMCC_FLAGS "${GIFSICLE_EMCC_FLAGS} -g2 -s ASSERTIONS=2")
    endif()
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS ${GIFSICLE_EMCC_FLAGS})
endif()

target_link_libraries(${TARGET_NAME} PUBLIC gifsicle)