#include "screens.hpp"

Screen::EditorScreen::EditorScreen(
    State *state,
    ::Properties *properties
) : state(state), properties(properties)
{

}

void Screen::EditorScreen::build()
{
    fileMenuBarUi.build();
    propertiesUi.build();
}