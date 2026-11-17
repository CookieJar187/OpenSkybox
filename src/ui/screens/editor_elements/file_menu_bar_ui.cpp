#include "editor_elements.hpp"

EditorElements::FileMenuBarUi::FileMenuBarUi(
    State *state
) : state(state)
{

}

void EditorElements::FileMenuBarUi::build()
{
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            if (ImGui::MenuItem("New", "Ctrl+N")) {
                // Handle New file
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                // Handle Open file
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                // Handle Save file
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Export", "Ctrl+E")) {
                state->setState(StateType::Export);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                state->setState(StateType::Exit);
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}