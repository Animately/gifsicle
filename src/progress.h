#pragma once

enum ProgressState
{
    None,
    Merging,
    Scaling,
    Optimizing,
    Writing,
    Finished
};

#ifdef __cplusplus
extern "C" {
#endif

void on_progress(int index);

void set_images_count(unsigned int images_count);
void set_progress_state(enum ProgressState progress_state);
void adjust_progress(unsigned int images_count);
int is_optimize();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <functional>
#include <map>

#include "utility.h"

class ProgressManager
{
public:
    static ProgressManager& instance();
    
    void setImagesCount(unsigned int images_count);
    void setOnProgress(std::function<void(int)> on_progress);
    void setProgressState(ProgressState progress_state);
    
    void applyOptions(const GifOptions& options);
    void adjustProgress(unsigned int images_count);
    void onProgress(int index);
    bool isOptimize() const;

    std::map<int, int> data;

private:
    ProgressManager();
    ProgressManager(const ProgressManager&) = default;

private:
    unsigned int m_states_count;
    unsigned int m_images_count;
    unsigned int m_total_count;
    float m_current_count;
    float m_progress;
    float m_progress_step;
    ProgressState m_progress_state;
    std::function<void(int)> m_on_progress;
    bool m_is_optimize;
};

#endif