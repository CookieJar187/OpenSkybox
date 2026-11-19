#pragma once

#include <filesystem>
#include <string>

#include "properties.hpp"

class SkyboxExporter
{
public:
    static const int minResolution = 4;
    static const int maxResolution = 8192;

    SkyboxExporter(
        unsigned int &shaderProgram,
        unsigned int &skyVAO,
        Properties &properties
    );

    void setExportPath(std::filesystem::path &path);
    void setResolution(int resolution);

    int getResolution();
    std::filesystem::path &getExportPath();
    std::string &getErrorMessage();

    bool isExportPathValid();
    int tryExportPng();

private:
    unsigned int &shaderProgram;
    unsigned int &skyVAO;
    Properties *properties;

    std::filesystem::path exportPath =
        std::filesystem::current_path();

    int resolution = 1024;

    std::string errorMessage;

    void exportPng();
};