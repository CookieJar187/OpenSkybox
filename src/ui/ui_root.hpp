#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "state.hpp"
#include "main_menu_screen.hpp"
#include "in_game_screen.hpp"
#include "properties.hpp"

class UiRoot{
private:
    State *state;
    Properties *properties;

    MainMenuScreen mainMenuScreen{state};
    InGameScreen inGameScreen{state, properties};
    
public:
    UiRoot(State &state, GLFWwindow *window, Properties &properties);

    void build();
    void draw();
    void destroy();
};