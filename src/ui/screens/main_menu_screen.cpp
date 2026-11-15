#include "screens.hpp"

Screen::MainMenuScreen::MainMenuScreen(State *state) : state(state) 
{

}

void Screen::MainMenuScreen::build()
{
    ImGui::Begin("OpenSkybox");

    ImGui::TextUnformatted("Welcome to OpenSkybox!");

    ImGui::TextWrapped("OpenSkybox is an open source software for creating realistic skyboxes.");

    if (ImGui::Button("Start"))
    {
        state->setState(StateType::Editor);
    }

    if (ImGui::Button("Tutorial"))
    {
        std::cout << "Implement tutorial here\n";
    }

    if (ImGui::Button("Exit App"))
    {
        state->setState(StateType::Exit);
    }

    ImGui::End();
}