#include <utility.h>
#include <gifsicle.h>
#include <progress.h>
#include <iostream>
#include "json.hpp"

extern "C" int gifsicle_main(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    using json = nlohmann::json;

    ProgressManager::instance().setOnProgress([](const auto value) { json j; j["type"] = "progress"; j["value"] = value; std::cout << j.dump() << std::endl; });

    return gifsicle_main(argc, argv);
}
