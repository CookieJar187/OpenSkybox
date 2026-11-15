#include "texture_loader.hpp"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <filesystem>
#include <iostream>

Texture TextureLoader::load(const std::string& path)
{
    Texture texture;

    stbi_set_flip_vertically_on_load(false);

    unsigned char* pixels = stbi_load(
        path.c_str(),
        &texture.width,
        &texture.height,
        &texture.channels,
        4
    );

    if (!pixels)
        throw std::runtime_error(
            "Failed to load texture: " + path +
            "\nReason: " + stbi_failure_reason()
        );

    texture.channels = 4;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        texture.width,
        texture.height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels
    );

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);

    return texture;
}

void TextureLoader::destroy(Texture &texture)
{
    if (texture.id == 0)
        return;

    glDeleteTextures(1, &texture.id);

    texture.id = 0;
    texture.width = 0;
    texture.height = 0;
    texture.channels = 0;
}