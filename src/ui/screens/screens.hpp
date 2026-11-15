#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "properties.hpp"

// ---- SCREENS ---- //

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
    Properties *properties;

public:
    EditorScreen(
        State *state,
        Properties *properties
    );

    void build();
};