#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GradientTransition
{
    float position = 0.0f;
    float width = 0.5f;

    static constexpr float minPosition = -1.0f;
    static constexpr float maxPosition = 1.0f;

    static constexpr float minWidth = 0.01f;
    static constexpr float maxWidth = 2.0f;
};

struct SolidColor
{
    float color[3] = {0.05f, 0.25f, 0.65f};
};
struct TwoColorGradient
{
    float zenith[3] = {0.65f, 0.80f, 0.95f};
    float nadir[3] = {0.25f, 0.35f, 0.45f};

    GradientTransition transition;
};
struct ThreeColorGradient
{
    float zenith[3] = {0.05f, 0.25f, 0.65f};
    float horizon[3] = {0.65f, 0.80f, 0.95f};
    float nadir[3] = {0.25f, 0.35f, 0.45f};

    GradientTransition upperTransition{0.5f, 0.5f};
    GradientTransition lowerTransition{-0.5f, 0.5f};
};

struct Properties
{
    // Atmosphere
    const char *atmosphereTypes[3] = {
        "Solid Color",
        "Two-Color Gradient",
        "Three-Color Gradient"
    };
    int currentAtmosphereType = 2;

    SolidColor solid;
    TwoColorGradient twoColor;
    ThreeColorGradient threeColor;

    // Sun
    bool sunEnabled = true;
    float sunColor[3] = {1.0f, 0.9f, 0.65f};
    float sunAzimuth = 0.0f;
    float sunElevation = 0.785398f;
    float sunIntensity = 1.0f;
    float sunGlare = 0.25f;
    float sunSize = 1.0f;

    // Clouds
    bool cloudsEnabled = true;
    float cloudCoverage = 0.5f;
    float cloudDensity = 0.7f;

    // Applying changes
    void apply(unsigned int shaderProgram)
    {
        // Atmosphere
        glUniform1i(
            glGetUniformLocation(shaderProgram, "atmosphereMode"),
            currentAtmosphereType
        );
        switch (currentAtmosphereType)
        {
            case 0:
                glUniform3fv(
                    glGetUniformLocation(shaderProgram, "solidColor"),
                    1,
                    solid.color
                );
                break;

            case 1:
                glUniform3fv(
                    glGetUniformLocation(shaderProgram, "zenithColor"),
                    1,
                    twoColor.zenith
                );
                glUniform3fv(
                    glGetUniformLocation(shaderProgram, "nadirColor"),
                    1,
                    twoColor.nadir
                );
                glUniform1f(
                    glGetUniformLocation(shaderProgram, "transitionPosition"),
                    twoColor.transition.position
                );
                glUniform1f(
                    glGetUniformLocation(shaderProgram, "transitionWidth"),
                    twoColor.transition.width
                );
                break;

            case 2:
                glUniform3fv(
                    glGetUniformLocation(shaderProgram, "zenithColor"),
                    1,
                    threeColor.zenith
                );
                glUniform3fv(
                    glGetUniformLocation(shaderProgram, "horizonColor"),
                    1,
                    threeColor.horizon
                );
                glUniform3fv(
                    glGetUniformLocation(shaderProgram, "nadirColor"),
                    1,
                    threeColor.nadir
                );
                glUniform1f(
                    glGetUniformLocation(shaderProgram, "upperTransitionPosition"),
                    threeColor.upperTransition.position
                );
                glUniform1f(
                    glGetUniformLocation(shaderProgram, "upperTransitionWidth"),
                    threeColor.upperTransition.width
                );
                glUniform1f(
                    glGetUniformLocation(shaderProgram, "lowerTransitionPosition"),
                    threeColor.lowerTransition.position
                );
                glUniform1f(
                    glGetUniformLocation(shaderProgram, "lowerTransitionWidth"),
                    threeColor.lowerTransition.width
                );
                break;

            default:
                std::cout << "Unsupported Atmosphere Type\n";
                break;

        }

        // Sun
        glUniform1i(
            glGetUniformLocation(shaderProgram, "sunEnabled"),
            sunEnabled ? 1 : 0
        );
        glUniform3fv(
            glGetUniformLocation(shaderProgram, "sunColor"),
            1,
            sunColor
        );
        glUniform1f(
            glGetUniformLocation(shaderProgram, "sunAzimuth"),
            sunAzimuth
        );
        glUniform1f(
            glGetUniformLocation(shaderProgram, "sunElevation"),
            sunElevation
        );
        glUniform1f(
            glGetUniformLocation(shaderProgram, "sunIntensity"),
            sunIntensity
        );
        glUniform1f(
            glGetUniformLocation(shaderProgram, "sunGlare"),
            sunGlare
        );
        glUniform1f(
            glGetUniformLocation(shaderProgram, "sunSize"),
            sunSize
        );
    }
};