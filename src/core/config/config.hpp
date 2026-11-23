#pragma once

#include <iostream>
#include <array>

class Config
{
friend class ConfigApplier;

private:
    // ---- SKY PROPERTIES ---- //
    struct Sky
    {
        // Dirty flag
        bool dirty = true;

        // Helper structs
        struct GradientTransition
        {
            float position = 0.0f;
            float width = 0.5f;

            static constexpr float minPosition = -1.0f;
            static constexpr float maxPosition = 1.0f;

            static constexpr float minWidth = 0.01f;
            static constexpr float maxWidth = 2.0f;
        } static gradientTransition;

        // Atmosphere
        const char *atmosphereTypes[3] = {
            "Solid Color",
            "Two-Color Gradient",
            "Three-Color Gradient"
        };
        int currentAtmosphereType = 2;

        struct SolidColor
        {
            std::array<float, 3> color =
                {0.05f, 0.25f, 0.65f};
        } solid;
        
        struct TwoColorGradient
        {
            std::array<float, 3> zenith =
                {0.65f, 0.80f, 0.95f};
            std::array<float, 3> nadir =
                {0.25f, 0.35f, 0.45f};

            GradientTransition transition;
        } twoColor;

        struct ThreeColorGradient
        {
            std::array<float, 3> zenith =
                {0.05f, 0.25f, 0.65f};
            std::array<float, 3> horizon =
                {0.65f, 0.80f, 0.95f};
            std::array<float, 3> nadir =
                {0.25f, 0.35f, 0.45f};

            GradientTransition upperTransition{0.5f, 0.5f};
            GradientTransition lowerTransition{-0.5f, 0.5f};
        } threeColor;

        // Sun
        bool sunEnabled = true;
        std::array<float, 3> sunColor = {1.0f, 0.9f, 0.65f};
        float sunAzimuth = 0.0f;
        float sunElevation = 0.785398f;
        float sunIntensity = 1.0f;
        float sunGlare = 0.25f;
        float sunSize = 1.0f;

        // Clouds
        bool cloudsEnabled = true;
        float cloudCoverage = 0.5f;
        float cloudDensity = 0.7f;

    } sky;

    // ---- CAMERA PROPERTIES ---- //
    struct Editor
    {
        // dirty flag
        bool dirty = true;

        // camera
        float fov = 70.0f;
        float mouseSensitivity = 0.15f;
        
    } editor;

public:
    const Sky &getSky() const;
    const Editor &getEditor() const;

    Sky &editSky();
    Editor &editEditor();
};