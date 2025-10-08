# Gifsicle version for WebAssembly

To build with Emscripten:

```bash
> emcmake cmake ..
> make
```

To cross compile for ARM:
```bash
> cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++
> make
```
