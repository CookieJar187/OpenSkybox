#include "editor_elements.hpp"

EditorElements::PropertiesUiElement::CloudsUi::CloudsUi(
    State *state,
    ::Properties *properties
) : state(state), properties(properties)
{

}

void EditorElements::PropertiesUiElement::CloudsUi::build()
{
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
}