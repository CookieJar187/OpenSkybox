#pragma once

#include <string>
#include <filesystem>

#include "properties.hpp"

class SkyboxExporter {
public:
    static const int minResolution = 16;
    static const int maxResolution = 8192;

    SkyboxExporter(
        unsigned int &shaderProgram,
        unsigned int &skyVAO,
        Properties &properties
    );

    void exportPNG();

    void setExportDirectory(
        std::filesystem::path &path
    );
    void setResolution(
        int resolution
    );

    int getResolution();
    std::filesystem::path &getExportDirectory();

private:
    unsigned int &shaderProgram;
    unsigned int &skyVAO;
    Properties *properties;

    std::filesystem::path exportDirectory;
    int resolution = 1024;
};