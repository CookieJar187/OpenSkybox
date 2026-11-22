#include "editor_elements.hpp"

EditorElements::PropertiesUiElement::CloudsUi::CloudsUi(
    State *state,
    Config *config
) : state(state), config(config)
{

}

void EditorElements::PropertiesUiElement::CloudsUi::build()
{
    if (ImGui::CollapsingHeader("Clouds"))
    {
        { // Clouds Enabled
            auto value = config->getSky().cloudsEnabled;

            if (ImGui::Checkbox(
                "Clouds Enabled",
                &value
            ))
                config->editSky().cloudsEnabled = value;
        }

        { // Cloud Coverage
            auto value = config->getSky().cloudCoverage;

            if (ImGui::DragFloat(
                "Cloud Coverage",
                &value,
                0.01f,
                0.0f,
                1.0f
            ))
                config->editSky().cloudCoverage = value;
        }

        { // Cloud Density
            auto value = config->getSky().cloudDensity;

            if (ImGui::DragFloat(
                "Cloud Density",
                &value,
                0.01f,
                0.0f,
                1.0f
            ))
                config->editSky().cloudDensity = value;

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Controls the thickness of the cloud layer.");
        }
    }
}