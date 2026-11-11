#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"

struct MainMenuScreen
{
private:
    State *state;

public:
    MainMenuScreen(State *state) : state(state) {};

    void build()
    {
        ImGui::Begin("OpenSkybox");

        ImGui::TextUnformatted("Welcome to OpenSkybox!");

        ImGui::TextWrapped("OpenSkybox is an open source software for creating realistic skyboxes.");

        if (ImGui::Button("Start"))
        {
            state->setState(StateType::InGame);
        }

        if (ImGui::Button("Tutorial"))
        {
            std::cout << "Implement tutorial here\n";
        }

        if (ImGui::Button("Exit App"))
        {
            state->setState(StateType::Exit);
        }

        ImGui::End();
    }
};