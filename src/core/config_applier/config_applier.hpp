#pragma once

#include "config.hpp"
#include "camera.hpp"

class ConfigApplier
{
private:
    Config *config;
    unsigned int shaderProgram;
    Camera *camera;

    void applySky();
    void applyEditor();

public:
    ConfigApplier(
        Config &config,
        unsigned int shaderProgram,
        Camera &camera
    );

    void applyIfDirty();
};