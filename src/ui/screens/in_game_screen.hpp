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

            if (ImGui::BeginCombo(
                "Atmosphere Type",
                properties->atmosphereTypes[properties->currentAtmosphereType]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(properties->atmosphereTypes); n++) {

                    bool is_selected = (properties->currentAtmosphereType == n);
                    
                    if (ImGui::Selectable(properties->atmosphereTypes[n], is_selected)) {
                        properties->currentAtmosphereType = n;
                    }
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            switch (properties->currentAtmosphereType)
            {
                case 0: // Solid Color
                    ImGui::ColorEdit3("Color", properties->solid.color);
                    break;

                case 1: // Two-Color Gradient
                    ImGui::ColorEdit3("Zenith", properties->twoColor.zenith);
                    ImGui::ColorEdit3("Nadir", properties->twoColor.nadir);
                    ImGui::DragFloat(
                        "Transition Position",
                        &properties->twoColor.transitionPosition,
                        0.005f,
                        0.0f,
                        0.5f
                    );
                    ImGui::DragFloat(
                        "Transition Width",
                        &properties->twoColor.transitionWidth,
                        0.005f,
                        0.0f,
                        0.5f
                    );

                    break;

                case 2: // Three-Color Gradient
                    ImGui::ColorEdit3("Zenith", properties->threeColor.zenith);
                    ImGui::ColorEdit3("Horizon", properties->threeColor.horizon);
                    ImGui::ColorEdit3("Nadir", properties->threeColor.nadir);
                    ImGui::DragFloat(
                        "Upper Transition Position",
                        &properties->threeColor.upperTransitionPosition,
                        0.005f,
                        0.0f,
                        0.5f
                    );
                    ImGui::DragFloat(
                        "Upper Transition Width",
                        &properties->threeColor.upperTransitionWidth,
                        0.005f,
                        0.0f,
                        0.5f
                    );
                    ImGui::DragFloat(
                        "Lower Transition Position",
                        &properties->threeColor.lowerTransitionPosition,
                        0.005f,
                        -0.5f,
                        0.0f
                    );
                    ImGui::DragFloat(
                        "Lower Transition Width",
                        &properties->threeColor.lowerTransitionWidth,
                        0.005f,
                        0.0f,
                        0.5f
                    );
                    break;
            }

            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Sun"))
        {
            ImGui::Indent();

            ImGui::Checkbox("Sun Enabled", &properties->sunEnabled);
            ImGui::ColorEdit3("Sun Color", properties->sunColor);
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
            ImGui::DragFloat(
                "Sun Glare",
                &properties->sunGlare,
                0.05f,
                0.0f,
                10.0f
            );
            ImGui::DragFloat(
                "Sun Size",
                &properties->sunSize,
                0.05f,
                0.0f,
                100.0f
            );
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Angular radius in degrees.");

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