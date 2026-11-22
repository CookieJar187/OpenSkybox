#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "file_dialog.hpp"

#include "state.hpp"
#include "config.hpp"
#include "screens.hpp"
#include "skybox_exporter.hpp"

class UiRoot{
private:
    State *state;
    Config *config;
    SkyboxExporter *skyboxExporter;

    FileDialog fileDialog;

    Screen::MainMenuScreen mainMenuScreen{state};
    Screen::EditorScreen editorScreen{state, config};
    Screen::ExportScreen exportScreen{
        state,
        config,
        skyboxExporter,
        fileDialog
    };
    
public:
    UiRoot(
        State &state,
        GLFWwindow *window,
        Config &config,
        SkyboxExporter &skyboxExporter
    );
    ~UiRoot();

    void build();
    void draw();
};