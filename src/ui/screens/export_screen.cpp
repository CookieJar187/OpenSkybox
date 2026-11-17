#include "screens.hpp"

#include "file_dialog.hpp"

Screen::ExportScreen::ExportScreen(
    State *state,
    ::Properties *properties,
    SkyboxExporter *skyboxExporter
) : state(state), properties(properties), skyboxExporter(skyboxExporter)
{
}

Screen::ExportScreen::~ExportScreen()
{
}

void Screen::ExportScreen::build() {

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Export", nullptr, flags);

    // TODO: Re-enable after fixing the native file dialog crash.
    // Known issue: The current implementation can crash the application.
    /*
    if (ImGui::Button("Export")) {

        skyboxExporter->exportPNG();
    }

    int resolution = skyboxExporter->getResolution();
    if (ImGui::DragInt(
        "Export Resolution",
        &resolution,
        SkyboxExporter::minResolution,
        SkyboxExporter::maxResolution
    )) {
        skyboxExporter->setResolution(resolution);
    }

    if (ImGui::Button("Choose Directory")) {

        std::optional<std::filesystem::path> dir =
            FileDialog::promptDirSelect();

        if (dir.has_value())
            skyboxExporter->setExportDirectory(dir.value());
    }

    */

    if (ImGui::Button("Close")) {
        state->setState(StateType::Editor);
    }

    ImGui::End();
}