#include <iostream>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "utility.h"
#include "gifsicle.h"
#include "progress.h"

using namespace emscripten;

val compress(const std::uintptr_t data, const std::size_t size, const GifOptions& gif_options, emscripten::val on_progress)
{
    COptions options;
    if (!parse_options(gif_options, options))
        return val::null();

    ProgressManager::instance().setOnProgress([on_progress](const auto value) { on_progress(value); });
    ProgressManager::instance().applyOptions(gif_options);

    const auto* input_buffer = reinterpret_cast<const uint8_t*>(data);

    GifBuffer buffer;
    const auto status = gifsicle_main(options.count(), options.options(), 
                                      input_buffer, size, &buffer.data, &buffer.size);  

    if (!buffer.data || status != 0) 
        return val::null();
    
    const auto Uint8ClampedArray = val::global("Uint8ClampedArray");
    return Uint8ClampedArray.new_(typed_memory_view(buffer.size, buffer.data));
}

EMSCRIPTEN_BINDINGS(GifSicle) 
{
    function("compress", &compress);

    value_object<GifOptions>("GifOptions")
        .field("lossy", &GifOptions::lossy)
        .field("optimize", &GifOptions::optimize)
        .field("scaleX", &GifOptions::scale_x)
        .field("scaleY", &GifOptions::scale_y)
        .field("colors", &GifOptions::colors);
}