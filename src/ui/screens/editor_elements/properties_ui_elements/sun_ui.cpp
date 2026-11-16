#include "editor_elements.hpp"

EditorElements::PropertiesUiElement::SunUi::SunUi(
    State *state,
    ::Properties *properties
) : state(state), properties(properties)
{

}

void EditorElements::PropertiesUiElement::SunUi::build()
{
    if (ImGui::CollapsingHeader("Sun"))
    {
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
    }
}