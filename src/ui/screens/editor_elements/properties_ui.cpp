#include "editor_elements.hpp"

EditorElements::PropertiesUi::PropertiesUi(
    State *state,
    ::Properties *properties
) : state(state), properties(properties)
{

}

void EditorElements::PropertiesUi::build()
{
    ImGui::Begin("Properties");

    atmosphereUi.build();
    sunUi.build();
    cloudsUi.build();

    ImGui::End();
}