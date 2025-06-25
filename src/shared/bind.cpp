#include <utility.h>
#include <gifsicle.h>
#include <progress.h>
#include "gifsicle_gif.h"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

namespace
{

std::vector<std::string> create_arguments(const char* args)
{
  if (!args || *args == '\0')
    return {};

  std::istringstream stream(args);
  std::vector<std::string> vargs;
  std::string arg;

  while (stream >> std::quoted(arg))
  {
    vargs.push_back(arg);
  }

  return vargs;
}

}  // namespace

extern "C" int gifsicle_main(int argc, const char *argv[]);

int gifsicle_process(const char* args)
{
    const auto vargs{create_arguments(args)};
    std::vector<const char*> argv(vargs.size());

    for (int32_t i{0}; i < vargs.size(); ++i)
    {
        argv[i] = vargs[i].c_str();
    }

    ProgressManager::instance().setOnProgress([](const auto value) { gifsicle_progress_callback(value); });

    return gifsicle_main(argv.size(), argv.data());
}
