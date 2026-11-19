#pragma once

#include <filesystem>

class FileDialog
{
public:
    FileDialog();
    ~FileDialog();

    std::filesystem::path promptDirSelect();
    std::filesystem::path promptImageSelect();
};