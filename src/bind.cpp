#include <iostream>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "coptions.h"
#include "gifsicle.h"

using namespace emscripten;

val compress(const std::uintptr_t data, const std::size_t size, const GifOptions& gif_options)
{
    COptions options;

    if (!parse_options(gif_options, options))
        return val::null();

    const auto* data_buffer = reinterpret_cast<const uint8_t*>(data);

    uint8_t* out_buffer = nullptr;
    uint32_t out_size = 0;

    const auto comp_result = gifsicle_main(options.count(), options.options(), data_buffer, size, &out_buffer, &out_size);

    if (!out_buffer || comp_result != 0) 
        return val::null();
    
    const auto Uint8ClampedArray = val::global("Uint8ClampedArray");
    return Uint8ClampedArray.new_(typed_memory_view(out_size, out_buffer));
}

EMSCRIPTEN_BINDINGS(GifSicle) 
{
   emscripten::function("compress", &compress);

    value_object<GifOptions>("GifOptions")
        .field("lossy", &GifOptions::lossy)
        .field("optimize", &GifOptions::optimize)
        .field("scale_x", &GifOptions::scale_x)
        .field("scale_y", &GifOptions::scale_y)
        .field("colors", &GifOptions::colors);
}