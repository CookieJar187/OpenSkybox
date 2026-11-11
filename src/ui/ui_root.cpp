#include "ui_root.hpp"

UiRoot::UiRoot(
    State &state,
    GLFWwindow *window,
    Properties &properties
) : state(&state), properties(&properties)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void UiRoot::build()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    switch (state->getState())
    {
    case (StateType::MainMenu):
        mainMenuScreen.build();
        break;

    case (StateType::InGame):
        inGameScreen.build();
        break;
    
    default:
        std::cout << "UiRoot: unsupported state type\n";
        break;
    }
}

void UiRoot::draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UiRoot::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}