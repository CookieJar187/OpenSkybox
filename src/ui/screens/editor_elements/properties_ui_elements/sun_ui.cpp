#include "editor_elements.hpp"

EditorElements::PropertiesUiElement::SunUi::SunUi(
    State *state,
    Config *config
) : state(state), config(config)
{

}

void EditorElements::PropertiesUiElement::SunUi::build()
{
    if (ImGui::CollapsingHeader("Sun"))
    {
        { // Sun Enabled
            auto value = config->getSky().sunEnabled;

            if (ImGui::Checkbox(
                "Sun Enabled",
                &value
            ))
                config->editSky().sunEnabled = value;
        }

        { // Sun Color
            auto value = config->getSky().sunColor;

            if (ImGui::ColorEdit3(
                "Sun Color",
                value.data()
            ))
                config->editSky().sunColor = value;
        }

        { // Sun Azimuth
            auto value = config->getSky().sunAzimuth;

            if (ImGui::SliderAngle(
                "Sun Azimuth",
                &value,
                -180.0f,
                180.0f
            ))
                config->editSky().sunAzimuth = value;
        }

        { // Sun Elevation
            auto value = config->getSky().sunAzimuth;

            if (ImGui::SliderAngle(
                "Sun Elevation",
                &value,
                -90.0f,
                90.0f
            ))
                config->editSky().sunElevation = value;
        }

        { // Sun Intensity
            auto value = config->getSky().sunIntensity;

            if (ImGui::DragFloat(
                "Sun Intensity",
                &value,
                0.05f,
                0.0f,
                10.0f
            ))
                config->editSky().sunIntensity = value;
        }

        { // Sun Glare
            auto value = config->getSky().sunGlare;

            if (ImGui::DragFloat(
                "Sun Glare",
                &value,
                0.05f,
                0.0f,
                10.0f
            ))
                config->editSky().sunGlare = value;
        }

        { // Sun Size
            auto value = config->getSky().sunSize;

            if (ImGui::DragFloat(
                "Sun Size",
                &value,
                0.05f,
                0.0f,
                100.0f
            ))
                config->editSky().sunSize = value;

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Angular radius in degrees.");
        }

    }
}