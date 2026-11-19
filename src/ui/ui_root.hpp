#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "file_dialog.hpp"

#include "state.hpp"
#include "properties.hpp"
#include "screens.hpp"
#include "skybox_exporter.hpp"

class UiRoot{
private:
    State *state;
    Properties *properties;
    SkyboxExporter *skyboxExporter;

    FileDialog fileDialog;

    Screen::MainMenuScreen mainMenuScreen{state};
    Screen::EditorScreen editorScreen{state, properties};
    Screen::ExportScreen exportScreen{
        state,
        properties,
        skyboxExporter,
        fileDialog
    };
    
public:
    UiRoot(
        State &state,
        GLFWwindow *window,
        Properties &properties,
        SkyboxExporter &skyboxExporter
    );
    ~UiRoot();

    void build();
    void draw();
};