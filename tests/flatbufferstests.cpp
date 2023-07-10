#include <filesystem>
#include <map>
#include <iostream>

#include "doctest/doctest.h"
#include "serialization/binary.h"
#include "testutils.h"

#include "gifsicle.h"
#include "lcdfgif/gif.h"

static void gifread_error(Gif_Stream* gfs, Gif_Image* gfi, int is_error, const char* error_text)
{
  if (is_error >= 0)
    std::cerr << "Error reading GIF: " << error_text << std::endl;
}

TEST_CASE("check gif flatbuffers")
{
  const std::map<std::string, std::string> gifs{
      {"07.gif", "07.flat"}, {"01.gif", "01.flat"}};

  for (const auto& [gif_name, flat_name] : gifs)
  {
    const std::filesystem::path gif_file{animately::testDirectoryPath() +
                                         "/gifs/" + gif_name};
    DOCTEST_REQUIRE_MESSAGE(std::filesystem::exists(gif_file),
                            "Input gif file doesn't exist");

    const std::filesystem::path gif_flat_file{
        animately::testDirectoryPath() + "/gifs/" + flat_name};
    DOCTEST_REQUIRE_MESSAGE(std::filesystem::exists(gif_flat_file),
                            "Input compressed gif file doesn't exist");

    const auto flat_bytes{
        animately::loadFile(gif_flat_file.u8string())};
    DOCTEST_REQUIRE_MESSAGE(
        !flat_bytes.empty(),
        "Input file is empty or error during file content loading");

    const auto gif_bytes{
        animately::loadFile(gif_file.u8string())};
    DOCTEST_REQUIRE_MESSAGE(
        !gif_bytes.empty(),
        "Input file is empty or error during file content loading");

    auto* fgif{from_flatbuffer(flat_bytes.data())};

    auto* gif{Gif_FullReadBuffer(reinterpret_cast<const uint8_t*>(gif_bytes.data()),
                      gif_bytes.size(), GIF_READ_UNCOMPRESSED,
                      "", gifread_error)};

    DOCTEST_REQUIRE_EQ(fgif->screen_height, gif->screen_height);
    DOCTEST_REQUIRE_EQ(fgif->screen_width, gif->screen_width);
    DOCTEST_REQUIRE_EQ(fgif->background, gif->background);
    DOCTEST_REQUIRE_EQ(fgif->loopcount, gif->loopcount);
    DOCTEST_REQUIRE_EQ(fgif->global->ncol, gif->global->ncol);
    DOCTEST_REQUIRE_EQ(fgif->nimages, gif->nimages);

    if (gif->global)
    {
      const auto* palette{gif->global};
      const auto* fpalette{fgif->global};

      DOCTEST_REQUIRE_EQ(palette->ncol, fpalette->ncol);

      for (size_t i{0}; i < palette->ncol; ++i)
      {
        DOCTEST_CHECK(GIF_COLOREQ(&palette->col[i], &fpalette->col[i]));
      }
    }

    for (size_t i{0}; i < gif->nimages; ++i)
    {
      const auto* image{gif->images[i]};
      const auto* fimage{fgif->images[i]};

      DOCTEST_REQUIRE_EQ(image->delay, fimage->delay);
      DOCTEST_REQUIRE_EQ(image->disposal, fimage->disposal);
      DOCTEST_REQUIRE_EQ(image->transparent, image->transparent);
      DOCTEST_REQUIRE_EQ(image->interlace, image->interlace);
      DOCTEST_REQUIRE_EQ(image->width, image->width);
      DOCTEST_REQUIRE_EQ(image->height, image->height);
      DOCTEST_REQUIRE_EQ(image->left, image->left);
      DOCTEST_REQUIRE_EQ(image->top, image->top);

      const auto& bitmap{image->image_data};
      const auto& fbitmap{fimage->image_data};

      for (size_t j{0}; j < image->width * image->height; ++j)
      {
        DOCTEST_CHECK_EQ(bitmap[j], fbitmap[j]);
      }
    }

    Gif_DeleteStream(gif);
    Gif_DeleteStream(fgif);
  }
}

TEST_CASE("lossy works with flatbuffer")
{
  const std::vector<std::string> gifs{"07.flat", "01.flat"};

  for (const auto& flat_name : gifs)
  {
    const std::filesystem::path gif_flat_file{
        animately::testDirectoryPath() + "/gifs/" + flat_name};
    DOCTEST_REQUIRE_MESSAGE(std::filesystem::exists(gif_flat_file),
                            "Input compressed gif file doesn't exist");

    const auto flat_bytes{
        animately::loadFile(gif_flat_file.u8string())};
    DOCTEST_REQUIRE_MESSAGE(
        !flat_bytes.empty(),
        "Input file is empty or error during file content loading");

    auto* fgif{deserialize(reinterpret_cast<const uint8_t*>(flat_bytes.data()), flat_bytes.size())};

    GifBuffer buffer;

    GifOptions options;
    options.lossy = 90;
    options.optimize = 1;
    options.reduce_frames = 0;
    options.colors = 256;
    options.scale_x = 1;
    options.scale_y = 1;

    COptions coptions;
    DOCTEST_REQUIRE(parse_options(options, coptions));
    DOCTEST_REQUIRE(gifsicle_main(coptions.count(), coptions.options(), fgif, &buffer.data, &buffer.size) == 0);
  }
}
