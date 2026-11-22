#include "config.hpp"

const Config::Sky &Config::getSky() const
{
    return sky;
}
const Config::Editor &Config::getEditor() const
{
    return editor;
}

Config::Sky &Config::editSky()
{
    sky.dirty = true;
    return sky;
}
Config::Editor &Config::editEditor()
{
    editor.dirty = true;
    return editor;
}