#include "editor_elements.hpp"

EditorElements::PropertiesUiElement::AtmosphereUi::AtmosphereUi(
    State *state,
    ::Properties *properties
) : state(state), properties(properties)
{

}

void EditorElements::PropertiesUiElement::AtmosphereUi::build()
{
    if (ImGui::CollapsingHeader("Atmosphere"))
    {
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
                    &properties->twoColor.transition.position,
                    0.005f,
                    GradientTransition::minPosition,
                    GradientTransition::maxPosition
                );
                ImGui::DragFloat(
                    "Transition Width",
                    &properties->twoColor.transition.width,
                    0.005f,
                    GradientTransition::minWidth,
                    GradientTransition::maxWidth
                );

                break;

            case 2: // Three-Color Gradient
                ImGui::ColorEdit3("Zenith", properties->threeColor.zenith);
                ImGui::ColorEdit3("Horizon", properties->threeColor.horizon);
                ImGui::ColorEdit3("Nadir", properties->threeColor.nadir);
                ImGui::DragFloat(
                    "Upper Transition Position",
                    &properties->threeColor.upperTransition.position,
                    0.005f,
                    GradientTransition::minPosition,
                    GradientTransition::maxPosition
                );
                ImGui::DragFloat(
                    "Upper Transition Width",
                    &properties->threeColor.upperTransition.width,
                    0.005f,
                    GradientTransition::minWidth,
                    GradientTransition::maxWidth
                );
                ImGui::DragFloat(
                    "Lower Transition Position",
                    &properties->threeColor.lowerTransition.position,
                    0.005f,
                    GradientTransition::minPosition,
                    GradientTransition::maxPosition
                );
                ImGui::DragFloat(
                    "Lower Transition Width",
                    &properties->threeColor.lowerTransition.width,
                    0.005f,
                    GradientTransition::minWidth,
                    GradientTransition::maxWidth
                );
                break;
        }
    }
}