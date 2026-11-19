#include "screens.hpp"

#include "texture_loader.hpp"

Screen::MainMenuScreen::MainMenuScreen(State *state) : state(state) 
{
    appIcon = TextureLoader::load("src/assets/icon.png");
}

Screen::MainMenuScreen::~MainMenuScreen()
{
    TextureLoader::destroy(appIcon);
}

void Screen::MainMenuScreen::build()
{
    // Window init
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoCollapse;

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowSize(
        ImVec2(viewport->Size.x * 0.4f, viewport->Size.y * 0.5f),
        ImGuiCond_FirstUseEver
    );

    ImGui::SetNextWindowPos(
        viewport->GetCenter(),
        ImGuiCond_FirstUseEver,
        ImVec2(0.5f, 0.5f)
    );

    bool open = true;

    ImGui::Begin("OpenSkybox", &open, flags);
    if (open == false)
        state->setState(StateType::Editor);

    // Text
    float width = ImGui::GetWindowWidth();

    ImGui::SetWindowFontScale(1.5f);
    const char* welcomeText = "Welcome to OpenSkybox!";
    float welcomeWidth = ImGui::CalcTextSize(welcomeText).x;
    ImGui::SetCursorPosX((width - welcomeWidth) * 0.5f);
    ImGui::TextUnformatted(welcomeText);
    ImGui::SetWindowFontScale(1.0f);

    ImGui::Image(
        (ImTextureID)(intptr_t)appIcon.id,
        ImVec2(128, 128)
    );

    ImGui::TextWrapped("OpenSkybox is a free, open-source skybox editor meant to provide a simple and intuitive way to create customizable skies for video games, animations, and other 3D media/applications.");
    ImGui::TextWrapped("The project aims to allow users to freely use the skyboxes they create, including in commercial projects, without royalties or attribution requirements.");
    ImGui::Separator();
    ImGui::TextWrapped("Early alpha - Software still in early development.");

    // Buttons
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
    ImGui::SetWindowFontScale(1.0f);

    ImGui::End();
}