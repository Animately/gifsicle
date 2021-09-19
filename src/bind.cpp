#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <stdio.h>
#include <vector>

using namespace emscripten;

extern "C" int gifsicle_main(int argc, const char *argv[], const uint8_t* buffer, size_t size, uint8_t** output_buffer, uint32_t* output_size);

val compress(const std::uintptr_t data, const std::size_t size)
{
    const auto* data_buffer = reinterpret_cast<const uint8_t*>(data);

    const char* args[] = {"", "-i", "data-file", "-O3", "--lossy=80", "-o", "data-file"};

    uint8_t* out_buffer = nullptr;
    uint32_t out_size = 0;

    const auto comp_result = gifsicle_main(7, args, data_buffer, size, &out_buffer, &out_size);

    if (out_buffer && comp_result == 0) 
    {
        const auto Uint8ClampedArray = val::global("Uint8ClampedArray");
        return Uint8ClampedArray.new_(typed_memory_view(out_size, out_buffer));
    }
    return val::null();
}

EMSCRIPTEN_BINDINGS(GifSicle) 
{
   emscripten::function("compress", &compress);
}