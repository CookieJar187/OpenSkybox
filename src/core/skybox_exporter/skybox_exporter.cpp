#include "skybox_exporter.hpp"
#include "properties.hpp"

#include <glad/glad.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <array>
#include <stdexcept>
#include <algorithm>
#include <vector>

SkyboxExporter::SkyboxExporter(
    unsigned int &shaderProgram,
    unsigned int &skyVAO,
    Properties &properties
) : shaderProgram(shaderProgram), skyVAO(skyVAO), properties(&properties)
{}

void SkyboxExporter::exportPNG() {

    if (resolution <= 0)
        throw std::runtime_error("Invalid skybox resolution");

    const std::array<const char*, 6> names = {
        "right", "left", "top",
        "bottom", "back", "front"
    };

    // Remember the caller's OpenGL state.
    GLint previousFramebuffer;
    GLint previousViewport[4];
    GLint previousProgram;
    GLint previousVAO;
    GLint previousPackAlignment;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);
    glGetIntegerv(GL_VIEWPORT, previousViewport);
    glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVAO);
    glGetIntegerv(GL_PACK_ALIGNMENT, &previousPackAlignment);

    GLuint framebuffer = 0;
    GLuint texture = 0;

    auto cleanup = [&]()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);
        glViewport(
            previousViewport[0], previousViewport[1],
            previousViewport[2], previousViewport[3]
        );
        glUseProgram(previousProgram);
        glBindVertexArray(previousVAO);
        glPixelStorei(GL_PACK_ALIGNMENT, previousPackAlignment);

        if (texture)
            glDeleteTextures(1, &texture);

        if (framebuffer)
            glDeleteFramebuffers(1, &framebuffer);
    };

    try
    {
        // Create offscreen color texture.
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA8,
            resolution, resolution, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        // Attach the texture to an offscreen framebuffer.
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            texture,
            0
        );

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw std::runtime_error("Skybox framebuffer is incomplete");

        glViewport(0, 0, resolution, resolution);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);

        glUseProgram(shaderProgram);
        properties->apply(shaderProgram);

        glUniform2f(
            glGetUniformLocation(shaderProgram, "uResolution"),
            static_cast<float>(resolution),
            static_cast<float>(resolution)
        );

        glUniform1i(
            glGetUniformLocation(shaderProgram, "exportMode"),
            1
        );

        glBindVertexArray(skyVAO);

        std::filesystem::create_directories(exportDirectory);

        std::vector<unsigned char> pixels(
            static_cast<size_t>(resolution) * resolution * 4
        );

        std::vector<unsigned char> flipped(pixels.size());

        for (int face = 0; face < 6; ++face)
        {
            glUniform1i(
                glGetUniformLocation(shaderProgram, "exportFace"),
                face
            );

            glDrawArrays(GL_TRIANGLES, 0, 3);

            glReadBuffer(GL_COLOR_ATTACHMENT0);
            glReadPixels(
                0, 0, resolution, resolution,
                GL_RGBA, GL_UNSIGNED_BYTE,
                pixels.data()
            );

            // OpenGL pixels start at the bottom.
            // PNG rows start at the top.
            const size_t stride = static_cast<size_t>(resolution) * 4;

            for (int y = 0; y < resolution; ++y)
            {
                const size_t source = static_cast<size_t>(resolution - 1 - y) * stride;
                const size_t target = static_cast<size_t>(y) * stride;

                std::copy_n(
                    pixels.data() + source,
                    stride,
                    flipped.data() + target
                );
            }

            auto path = std::filesystem::path(exportDirectory)
                      / (std::string(names[face]) + ".png");

            if (!stbi_write_png(
                path.string().c_str(),
                resolution, resolution,
                4, flipped.data(),
                static_cast<int>(stride)
            ))
            {
                throw std::runtime_error(
                    "Failed to write skybox image: " + path.string()
                );
            }
        }

        glUniform1i(
            glGetUniformLocation(shaderProgram, "exportMode"),
            0
        );
    }
    catch (...)
    {
        cleanup();
        throw;
    }

    cleanup();
}

void SkyboxExporter::setExportDirectory(
    std::filesystem::path &path
) {
    exportDirectory = path;
}

void SkyboxExporter::setResolution(
    int value
) {
    if (value >= minResolution && value <= maxResolution)
        resolution = value;
}

int SkyboxExporter::getResolution() {
    return resolution;
}
std::filesystem::path &SkyboxExporter::getExportDirectory() {
    return exportDirectory;
}