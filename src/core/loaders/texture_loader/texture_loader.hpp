#pragma once

#include <string>

#include "texture.hpp"

namespace TextureLoader
{
    Texture load(const std::string &path);
    void destroy(Texture &texture);
};