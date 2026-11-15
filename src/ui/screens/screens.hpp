#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "properties.hpp"

#include "editor_elements.hpp"

// ---- SCREENS ---- //

namespace Screen
{
    // Main Menu
    struct MainMenuScreen
    {
    private:
        State *state;

    public:
        MainMenuScreen(State *state);

        void build();
    };

    // Editor
    struct EditorScreen
    {
    private:
        State *state;
        ::Properties *properties;

        EditorElements::FileMenuBarUi fileMenuBarUi{state};
        EditorElements::PropertiesUi propertiesUi{state, properties};

    public:
        EditorScreen(
            State *state,
            ::Properties *properties
        );

        void build();
    };
}