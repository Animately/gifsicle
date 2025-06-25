#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

  int gifsicle_process(const char* arguments);

  extern void gifsicle_progress_callback(int value)
      __attribute__((weak_import));

#ifdef __cplusplus
}
#endif
