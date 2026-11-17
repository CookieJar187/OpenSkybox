#include "file_dialog.hpp"

#include <iostream>
#include <stdexcept>

#include <nfd.h>

std::optional<std::filesystem::path>
    FileDialog::promptDirSelect() {

    try {

        if (NFD_Init() != NFD_OKAY)
            throw std::runtime_error(NFD_GetError());

        nfdu8char_t *outPath;
        nfdresult_t result = NFD_PickFolderU8(&outPath, nullptr);

        if (result == NFD_OKAY) {

            std::filesystem::path path =
                std::filesystem::u8path(outPath);

            NFD_FreePathU8(outPath);

            return path;
        }
        else if (result == NFD_CANCEL) {

            std::cout << "User pressed cancel\n";
        }
        else {

            printf("FileDialog error: %s\n", NFD_GetError());
        }

        NFD_Quit();
    }
    catch(std::exception& e) {

        std::cerr << "FileDialog error: " << e.what() << std::endl;
    }

    return std::nullopt;
}

std::optional<std::filesystem::path>
    FileDialog::promptImageSelect() {

    try {

        if (NFD_Init() != NFD_OKAY)
            throw std::runtime_error(NFD_GetError());

        nfdu8char_t *outPath;
        nfdu8filteritem_t filters[1] = {
            { "Images", "png,jpg,jpeg" }
        };
        nfdopendialogu8args_t args = {0};
        args.filterList = filters;
        args.filterCount = 1;
        nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);

        if (result == NFD_OKAY) {
            
            std::filesystem::path path =
                std::filesystem::u8path(outPath);

            NFD_FreePathU8(outPath);

            return path;
        }
        else if (result == NFD_CANCEL) {

            std::cout << "User pressed cancel\n";
        }
        else {

            printf("FileDialog error: %s\n", NFD_GetError());
        }

        NFD_Quit();
    }
    catch(std::exception& e) {

        std::cerr << "FileDialog error: " << e.what() << std::endl;
    }

    return std::nullopt;
}