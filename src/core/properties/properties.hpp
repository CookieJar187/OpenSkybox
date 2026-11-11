#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Properties
{
    // Atmosphere
    float zenithColor[3] = {0.05f, 0.25f, 0.65f};
    float horizonColor[3] = {0.65f, 0.80f, 0.95f};
    float nadirColor[3] = {0.25f, 0.35f, 0.45f};

    // Sun
    bool sunEnabled = true;
    float sunAzimuth = 0.0f;
    float sunElevation = 45.0f;
    float sunIntensity = 1.0f;

    // Clouds
    bool cloudsEnabled = true;
    float cloudCoverage = 0.5f;
    float cloudDensity = 0.7f;

    // Applying changes
    void apply(unsigned int shaderProgram)
    {
        // Atmosphere
        glUniform3fv(
            glGetUniformLocation(shaderProgram, "zenithColor"),
            1,
            zenithColor
        );

        glUniform3fv(
            glGetUniformLocation(shaderProgram, "horizonColor"),
            1,
            horizonColor
        );

        glUniform3fv(
            glGetUniformLocation(shaderProgram, "nadirColor"),
            1,
            nadirColor
        );
    }
};