#pragma once

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.hpp"
#include "properties.hpp"

struct InGameScreen
{
private:
    State *state;
    Properties *properties;

public:
    InGameScreen(
        State *state,
        Properties *properties
    ) : state(state), properties(properties) {};

    void build()
    {
        // File menu bar
        if (ImGui::BeginMainMenuBar()) {

            if (ImGui::BeginMenu("File")) {

                if (ImGui::MenuItem("New", "Ctrl+N")) {
                    // Handle New file
                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    // Handle Open file
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                    // Handle Save file
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) {
                    state->setState(StateType::Exit);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        // Properties
        ImGui::Begin("Properties");

        if (ImGui::CollapsingHeader("Atmosphere"))
        {
            ImGui::Indent();

            ImGui::ColorEdit3("Zenith Color", properties->zenithColor);
            ImGui::ColorEdit3("Horizon Color", properties->horizonColor);
            ImGui::ColorEdit3("Nadir Color", properties->nadirColor);

            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Sun"))
        {
            ImGui::Indent();

            ImGui::Checkbox("Sun Enabled", &properties->sunEnabled);
            ImGui::SliderAngle(
                "Sun Azimuth",
                &properties->sunAzimuth,
                -180.0f,
                180.0f
            );
            ImGui::SliderAngle(
                "Sun Elevation",
                &properties->sunElevation,
                -90.0f,
                90.0f
            );
            ImGui::DragFloat(
                "Sun Intensity",
                &properties->sunIntensity,
                0.05f,
                0.0f,
                10.0f
            );

            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Clouds"))
        {
            ImGui::Indent();

            ImGui::Checkbox("Clouds Enabled", &properties->cloudsEnabled);
            ImGui::DragFloat(
                "Cloud Coverage",
                &properties->cloudCoverage,
                0.01f,
                0.0f,
                1.0f
            );
            ImGui::DragFloat(
                "Cloud Density",
                &properties->cloudDensity,
                0.01f,
                0.0f,
                1.0f
            );
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Controls the thickness of the cloud layer.");

            ImGui::Unindent();
        }

        ImGui::End();
    }
};