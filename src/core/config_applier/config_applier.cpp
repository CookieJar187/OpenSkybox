#include "config_applier.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ConfigApplier::ConfigApplier(
    Config &config,
    unsigned int shaderProgram,
    Camera &camera
) :
    config(&config),
    shaderProgram(shaderProgram),
    camera(&camera)
{}

void ConfigApplier::applySky()
{
    // Atmosphere
    glUniform1i(
        glGetUniformLocation(shaderProgram, "atmosphereMode"),
        config->sky.currentAtmosphereType
    );
    switch (config->sky.currentAtmosphereType)
    {
        case 0:
            glUniform3fv(
                glGetUniformLocation(shaderProgram, "solidColor"),
                1,
                config->sky.solid.color.data()
            );
            break;

        case 1:
            glUniform3fv(
                glGetUniformLocation(shaderProgram, "zenithColor"),
                1,
                config->sky.twoColor.zenith.data()
            );
            glUniform3fv(
                glGetUniformLocation(shaderProgram, "nadirColor"),
                1,
                config->sky.twoColor.nadir.data()
            );
            glUniform1f(
                glGetUniformLocation(shaderProgram, "transitionPosition"),
                config->sky.twoColor.transition.position
            );
            glUniform1f(
                glGetUniformLocation(shaderProgram, "transitionWidth"),
                config->sky.twoColor.transition.width
            );
            break;

        case 2:
            glUniform3fv(
                glGetUniformLocation(shaderProgram, "zenithColor"),
                1,
                config->sky.threeColor.zenith.data()
            );
            glUniform3fv(
                glGetUniformLocation(shaderProgram, "horizonColor"),
                1,
                config->sky.threeColor.horizon.data()
            );
            glUniform3fv(
                glGetUniformLocation(shaderProgram, "nadirColor"),
                1,
                config->sky.threeColor.nadir.data()
            );
            glUniform1f(
                glGetUniformLocation(shaderProgram, "upperTransitionPosition"),
                config->sky.threeColor.upperTransition.position
            );
            glUniform1f(
                glGetUniformLocation(shaderProgram, "upperTransitionWidth"),
                config->sky.threeColor.upperTransition.width
            );
            glUniform1f(
                glGetUniformLocation(shaderProgram, "lowerTransitionPosition"),
                config->sky.threeColor.lowerTransition.position
            );
            glUniform1f(
                glGetUniformLocation(shaderProgram, "lowerTransitionWidth"),
                config->sky.threeColor.lowerTransition.width
            );
            break;

        default:
            std::cout << "Unsupported Atmosphere Type\n";
            break;

    }

    // Sun
    glUniform1i(
        glGetUniformLocation(shaderProgram, "sunEnabled"),
        config->sky.sunEnabled ? 1 : 0
    );
    glUniform3fv(
        glGetUniformLocation(shaderProgram, "sunColor"),
        1,
        config->sky.sunColor.data()
    );
    glUniform1f(
        glGetUniformLocation(shaderProgram, "sunAzimuth"),
        config->sky.sunAzimuth
    );
    glUniform1f(
        glGetUniformLocation(shaderProgram, "sunElevation"),
        config->sky.sunElevation
    );
    glUniform1f(
        glGetUniformLocation(shaderProgram, "sunIntensity"),
        config->sky.sunIntensity
    );
    glUniform1f(
        glGetUniformLocation(shaderProgram, "sunGlare"),
        config->sky.sunGlare
    );
    glUniform1f(
        glGetUniformLocation(shaderProgram, "sunSize"),
        config->sky.sunSize
    );

    // Unmark dirty
    config->sky.dirty = false;
}

void ConfigApplier::applyEditor()
{
    glUniform1f(
        glGetUniformLocation(shaderProgram, "uCameraFov"),
        config->editor.fov
    );

    camera->setSensitivity(config->editor.mouseSensitivity);

    // Unmark dirty
    config->editor.dirty = false;
}

void ConfigApplier::applyIfDirty()
{
    if (config->sky.dirty)
    {
        applySky();
    }
    if (config->editor.dirty)
    {
        applyEditor();
    }
}