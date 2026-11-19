#include "screens.hpp"

Screen::ExportScreen::ExportScreen(
    State *state,
    Properties *properties,
    SkyboxExporter *skyboxExporter,
    FileDialog &fileDialog
) :
    state(state),
    properties(properties),
    skyboxExporter(skyboxExporter),
    fileDialog(&fileDialog)
{}

Screen::ExportScreen::~ExportScreen() {}

void Screen::ExportScreen::build() {

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoCollapse;

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowSize(
        ImVec2(viewport->Size.x * 0.5f, viewport->Size.y * 0.5f),
        ImGuiCond_FirstUseEver
    );

    ImGui::SetNextWindowPos(
        viewport->GetCenter(),
        ImGuiCond_FirstUseEver,
        ImVec2(0.5f, 0.5f)
    );

    ImGui::Begin("Export", nullptr, flags);

    // Resolution
    int resolution = skyboxExporter->getResolution();
    if (ImGui::DragInt(
        "Export Resolution",
        &resolution,
        0.5f,
        SkyboxExporter::minResolution,
        SkyboxExporter::maxResolution
    )) {
        skyboxExporter->setResolution(resolution);
    }

    // Directory
    std::filesystem::path dir =
        skyboxExporter->getExportPath();

    // Export path validity
    if (!skyboxExporter->isExportPathValid())
    {
        ImGui::TextUnformatted("Invalid Export Path, Check Again.");
    }
    else
        ImGui::TextUnformatted("Export Path OK.");

    // Export path input
    char dirString[256];
    strcpy(dirString, dir.c_str());

    bool enterPressed = ImGui::InputText(
        "Export Path",
        dirString,
        sizeof(dirString),
        ImGuiInputTextFlags_EnterReturnsTrue
    );

    bool editingFinished = ImGui::IsItemDeactivatedAfterEdit();
    if (enterPressed || editingFinished)
    {
        std::filesystem::path newPath{dirString};
        skyboxExporter->setExportPath(newPath);
    }

    // Choose export path button
    if (ImGui::Button("Choose Export Path")) {

        std::filesystem::path newDir =
            fileDialog->promptDirSelect();

        if (std::filesystem::is_directory(newDir))
            skyboxExporter->setExportPath(newDir);
    }

    if (ImGui::Button("Close")) {
        state->setState(StateType::Editor);
    }

    // Export button
    if (ImGui::Button("Export"))
    {
        int exportStatus =
            skyboxExporter->tryExportPng();

        if (exportStatus == 1)
        {
            ImGui::OpenPopup("Export Error");
        }
        else if (exportStatus == 0)
        {
            ImGui::OpenPopup("Export Successful");
        }
    }

    // Popups
    if (ImGui::BeginPopup("Export Error"))
    {
        ImGui::TextUnformatted("Export Failed.");
        ImGui::TextUnformatted(skyboxExporter->getErrorMessage().c_str());

        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Export Successful"))
    {
        ImGui::TextUnformatted("Exported Successfully!");

        if (ImGui::Button("OK"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    ImGui::End();
}