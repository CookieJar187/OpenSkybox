#include "editor_elements.hpp"

EditorElements::CameraSettingsUi::CameraSettingsUi(
    Config *config
) : config(config) {}

void EditorElements::CameraSettingsUi::build()
{
    ImGui::Begin("Camera Settings");

    { // Field of View
        auto value = config->getEditor().fov;

        if (ImGui::DragFloat(
            "Field of View",
            &value,
            0.5f,
            30.0f,
            130.0f
        ))
            config->editEditor().fov = value;
    }

    { // Mouse Sensitivity
        auto value = config->getEditor().mouseSensitivity;

        if (ImGui::DragFloat(
            "Mouse Sensitivity",
            &value,
            0.01f,
            0.0f,
            1.0f
        ))
            config->editEditor().mouseSensitivity = value;
    }

    ImGui::End();
}