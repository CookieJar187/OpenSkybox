#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

#include "state.hpp"
#include "main_menu_screen.hpp"

class UiRoot{
private:
    State *state;

    MainMenuScreen mainMenuScreen{state};
    
public:
    UiRoot(State &state, GLFWwindow *window);

    void build();
    void draw();
    void destroy();
};