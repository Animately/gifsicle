#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void on_progress(int index);

void set_images_count(unsigned int images_count);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <functional>

#include "utility.h"

class ProgressManager
{
public:
    static ProgressManager& instance();

    void setImagesCount(unsigned int images_count);
    void onProgress(unsigned int progress);
    void setOnProgress(std::function<void(int)> on_progress);

private:
    ProgressManager();
    ProgressManager(const ProgressManager&) = default;

private:
    unsigned int m_images_count;
    unsigned int m_total_count;
    unsigned int m_current_progress;

    std::function<void(int)> m_on_progress;
};

#endif
