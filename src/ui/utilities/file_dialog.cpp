#include "file_dialog.hpp"

#include <iostream>
#include <stdexcept>

#include <nfd.h>

FileDialog::FileDialog()
{
    if (NFD_Init() != NFD_OKAY)
        throw std::runtime_error(NFD_GetError());
}

FileDialog::~FileDialog()
{
    NFD_Quit();
}

std::filesystem::path FileDialog::promptDirSelect() {

    nfdu8char_t *outPath = nullptr;
    bool pathPicked = false;

    try {
        nfdresult_t result = NFD_PickFolderU8(&outPath, nullptr);

        if (result == NFD_OKAY)
        {
            pathPicked = true;

            std::filesystem::path path =
                std::filesystem::u8path(outPath);

            NFD_FreePathU8(outPath);
            return path;
        }
        else if (result == NFD_ERROR)
        {
            std::cerr << "FileDialog error: "
                << NFD_GetError() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "FileDialog error: " << e.what() << std::endl;
    }

    if (pathPicked)
        NFD_FreePathU8(outPath);

    return std::filesystem::path{};
}

std::filesystem::path FileDialog::promptImageSelect() {

    nfdu8char_t *outPath = nullptr;
    bool pathPicked = false;

    try {
        nfdu8filteritem_t filters[1] = {
            { "Images", "png,jpg,jpeg" }
        };
        nfdopendialogu8args_t args = {};
        args.filterList = filters;
        args.filterCount = 1;
        nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);

        if (result == NFD_OKAY)
        {
            pathPicked = true;

            std::filesystem::path path =
                std::filesystem::u8path(outPath);

            NFD_FreePathU8(outPath);
            return path;
        }
        else if (result == NFD_ERROR)
        {
            std::cerr << "FileDialog error: "
                << NFD_GetError() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "FileDialog error: " << e.what() << std::endl;
    }

    if (pathPicked)
        NFD_FreePathU8(outPath);

    return std::filesystem::path{};
}