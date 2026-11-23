#include "editor_elements.hpp"

EditorElements::PropertiesUiElement::AtmosphereUi::AtmosphereUi(
    State *state,
    Config *config
) : state(state), config(config)
{

}

void EditorElements::PropertiesUiElement::AtmosphereUi::build()
{
    if (ImGui::CollapsingHeader("Atmosphere"))
    {
        if (ImGui::BeginCombo(
            "Atmosphere Type",
            config->getSky().atmosphereTypes[config->getSky().currentAtmosphereType]
        ))
        {
            for (int n = 0; n < IM_ARRAYSIZE(config->getSky().atmosphereTypes); n++)
            {
                bool is_selected = (config->getSky().currentAtmosphereType == n);
                
                if (ImGui::Selectable(config->getSky().atmosphereTypes[n], is_selected))
                {
                    config->editSky().currentAtmosphereType = n;
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        switch (config->getSky().currentAtmosphereType)
        {
            case 0: // Solid Color

                { // Color
                    auto value = config->getSky().solid.color;

                    if (ImGui::ColorEdit3(
                        "Color",
                        value.data()
                    ))
                        config->editSky().solid.color = value;
                }

                break;

            case 1: // Two-Color Gradient

                { // Zenith
                    auto value = config->getSky().twoColor.zenith;

                    if (ImGui::ColorEdit3(
                        "Zenith",
                        value.data()
                    ))
                        config->editSky().twoColor.zenith = value;
                }

                { // Nadir
                    auto value = config->getSky().twoColor.nadir;

                    if (ImGui::ColorEdit3(
                        "Nadir",
                        value.data()
                    ))
                        config->editSky().twoColor.nadir = value;
                }

                { // Transition Position
                    auto value = config->getSky().twoColor.transition.position;

                    if (ImGui::DragFloat(
                        "Transition Position",
                        &value,
                        0.005f,
                        config->getSky().gradientTransition.minPosition,
                        config->getSky().gradientTransition.maxPosition
                    ))
                        config->editSky().twoColor.transition.position = value;
                }

                { // Transition Width
                    auto value = config->getSky().twoColor.transition.width;

                    if (ImGui::DragFloat(
                        "Transition Width",
                        &value,
                        0.005f,
                        config->getSky().gradientTransition.minWidth,
                        config->getSky().gradientTransition.maxWidth
                    ))
                        config->editSky().twoColor.transition.width = value;
                }

                break;

            case 2: // Three-Color Gradient

                { // Zenith
                    auto value = config->getSky().threeColor.zenith;

                    if (ImGui::ColorEdit3(
                        "Zenith",
                        value.data()
                    ))
                        config->editSky().threeColor.zenith = value;
                }

                { // Horizon
                    auto value = config->getSky().threeColor.horizon;

                    if (ImGui::ColorEdit3(
                        "Horizon",
                        value.data()
                    ))
                        config->editSky().threeColor.horizon = value;
                }

                { // Nadir
                    auto value = config->getSky().threeColor.nadir;

                    if (ImGui::ColorEdit3(
                        "Nadir",
                        value.data()
                    ))
                        config->editSky().threeColor.nadir = value;
                }

                { // Upper Transition Position
                    auto value = config->getSky().threeColor.upperTransition.position;

                    if (ImGui::DragFloat(
                        "Upper Transition Position",
                        &value,
                        0.005f,
                        config->getSky().gradientTransition.minPosition,
                        config->getSky().gradientTransition.maxPosition
                    ))
                        config->editSky().threeColor.upperTransition.position = value;
                }

                { // Upper Transition Width
                    auto value = config->getSky().threeColor.upperTransition.width;

                    if (ImGui::DragFloat(
                        "Upper Transition Width",
                        &value,
                        0.005f,
                        config->getSky().gradientTransition.minWidth,
                        config->getSky().gradientTransition.maxWidth
                    ))
                        config->editSky().threeColor.upperTransition.width = value;
                }

                { // Lower Transition Position
                    auto value = config->getSky().threeColor.lowerTransition.position;

                    if (ImGui::DragFloat(
                        "Lower Transition Position",
                        &value,
                        0.005f,
                        config->getSky().gradientTransition.minPosition,
                        config->getSky().gradientTransition.maxPosition
                    ))
                        config->editSky().threeColor.lowerTransition.position = value;
                }

                { // Lower Transition Width
                    auto value = config->getSky().threeColor.lowerTransition.width;

                    if (ImGui::DragFloat(
                        "Lower Transition Width",
                        &value,
                        0.005f,
                        config->getSky().gradientTransition.minWidth,
                        config->getSky().gradientTransition.maxWidth
                    ))
                        config->editSky().threeColor.lowerTransition.width = value;
                }

                break;
        }
    }
}