#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "state.hpp"
#include "properties.hpp"
#include "screens.hpp"
#include "skybox_exporter.hpp"

class UiRoot{
private:
    State *state;
    Properties *properties;
    SkyboxExporter *skyboxExporter;

    Screen::MainMenuScreen mainMenuScreen{state};
    Screen::EditorScreen editorScreen{state, properties};
    Screen::ExportScreen exportScreen{state, properties, skyboxExporter};
    
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