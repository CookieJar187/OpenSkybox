#include "screens.hpp"

Screen::EditorScreen::EditorScreen(
    State *state,
    Config *config
) : state(state), config(config)
{

}

void Screen::EditorScreen::build()
{
    fileMenuBarUi.build();
    propertiesUi.build();
    cameraSettingsUi.build();
}