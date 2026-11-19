#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "properties.hpp"

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
        Properties *properties;

        EditorElements::FileMenuBarUi fileMenuBarUi{state};
        EditorElements::PropertiesUi propertiesUi{state, properties};

    public:
        EditorScreen(
            State *state,
            Properties *properties
        );

        void build();
    };

    // Export
    struct ExportScreen {
    private:
        State *state;
        Properties *properties;
        SkyboxExporter *skyboxExporter;

        FileDialog *fileDialog;

    public:
        ExportScreen(
            State *state,
            Properties *properties,
            SkyboxExporter *skyboxExporter,
            FileDialog &fileDialog
        );
        ~ExportScreen();

        void build();
    };
}