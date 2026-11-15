#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "state.hpp"
#include "properties.hpp"
#include "screens.hpp"

class UiRoot{
private:
    State *state;
    Properties *properties;

    MainMenuScreen mainMenuScreen{state};
    EditorScreen editorScreen{state, properties};
    
public:
    UiRoot(State &state, GLFWwindow *window, Properties &properties);

    void build();
    void draw();
    void destroy();
};