#include "editor_elements.hpp"

EditorElements::PropertiesUi::PropertiesUi(
    State *state,
    Config *config
) : state(state), config(config)
{

}

void EditorElements::PropertiesUi::build()
{
    ImGui::Begin("SkyConfig");

    atmosphereUi.build();
    sunUi.build();
    cloudsUi.build();

    ImGui::End();
}