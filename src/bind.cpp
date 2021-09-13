#include <iostream>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <stdio.h>
#include <vector>

using namespace emscripten;

extern "C" int gifsicle_main(int argc, const char *argv[], const uint8_t* buffer, std::size_t size);

val compress(const std::uintptr_t data, const std::size_t size)
{
    const auto* data_buffer = reinterpret_cast<const uint8_t*>(data);

    const char* args[] = {"", "-i", "data-file", "-O3", "--lossy=80", "-o", "test.gif"};
    const auto comp_result = gifsicle_main(7, args, data_buffer, size);

    FILE *fp = fopen("test.gif", "r");
    if (fp != NULL) 
    {
        std::vector<uint8_t> result;

        if (fseek(fp, 0L, SEEK_END) == 0) 
        {
            long bufsize = ftell(fp);

            result.resize(bufsize);

            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

            size_t newLen = fread(result.data(), sizeof(uint8_t), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            }
            else
            {
                fclose(fp);
                const auto Uint8ClampedArray = val::global("Uint8ClampedArray");
                return Uint8ClampedArray.new_(typed_memory_view(result.size(), result.data()));
            }
        }
    }
    return val::null();
}

EMSCRIPTEN_BINDINGS(GifSicle) 
{
   emscripten::function("compress", &compress);
}