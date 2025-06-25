#include <progress.h>

#include <map>
#include <math.h>

#include <iostream>

ProgressManager::ProgressManager()
: m_images_count(0)
, m_current_progress(0)
{
}

void ProgressManager::setImagesCount(unsigned int images_count)
{
    m_images_count = images_count;
}

void ProgressManager::setOnProgress(std::function<void(int)> on_progress)
{
    m_on_progress = on_progress;
}

void ProgressManager::onProgress(unsigned int progress)
{
  auto p = static_cast<unsigned int>(static_cast<float>(progress) / static_cast<float>(m_images_count) * 100.f);
  if (p == m_current_progress)
    return;

  m_current_progress = p;
  if (m_on_progress)
    m_on_progress(m_current_progress);
}

ProgressManager& ProgressManager::instance()
{
    static ProgressManager progress_manager;
    return progress_manager;
}

void on_progress(int index)
{
    ProgressManager::instance().onProgress(index);
}

void set_images_count(unsigned int images_count)
{
    ProgressManager::instance().setImagesCount(images_count);
}
