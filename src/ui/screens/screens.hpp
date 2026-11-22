#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "config.hpp"

#include "editor_elements.hpp"
#include "file_dialog.hpp"

#include "texture.hpp"

#include "skybox_exporter.hpp"

// ---- SCREENS ---- //

namespace Screen
{
    // Main Menu
    struct MainMenuScreen {
    private:
        State *state;
        Texture appIcon;

    public:
        MainMenuScreen(State *state);
        ~MainMenuScreen();

        void build();
    };

    // Editor
    struct EditorScreen {
    private:
        State *state;
        Config *config;

        EditorElements::FileMenuBarUi fileMenuBarUi{state};
        EditorElements::PropertiesUi propertiesUi{state, config};
        EditorElements::CameraSettingsUi cameraSettingsUi{config};

    public:
        EditorScreen(
            State *state,
            Config *config
        );

        void build();
    };

    // Export
    struct ExportScreen {
    private:
        State *state;
        Config *config;
        SkyboxExporter *skyboxExporter;

        FileDialog *fileDialog;

    public:
        ExportScreen(
            State *state,
            Config *config,
            SkyboxExporter *skyboxExporter,
            FileDialog &fileDialog
        );
        ~ExportScreen();

        void build();
    };
}