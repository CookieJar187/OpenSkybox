#pragma once

#include "config.hpp"

class ConfigApplier
{
private:
    Config *config;
    unsigned int shaderProgram;

    void applySky();
    void applyEditor();

public:
    ConfigApplier(
        Config &config,
        unsigned int shaderProgram
    );

    void applyIfDirty();
};