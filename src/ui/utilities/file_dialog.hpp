#pragma once

#include <filesystem>
#include <optional>

namespace FileDialog {

    std::optional<std::filesystem::path>
        promptDirSelect();

    std::optional<std::filesystem::path>
        promptImageSelect();
}