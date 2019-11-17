//
// Created by trojan52.
//

#include <algorithm>

#include "Definitions.h"

std::vector<std::string> ExtractFilesFromPath(const std::string &sPath)
{
    namespace fs = std::filesystem;
    std::vector<std::string> vFiles;
    if (!sPath.empty())
    {
        fs::path fsPath(sPath);

        if (fsPath.has_filename())
        {
            // If we have only one file then make sure that this file
            // exists and add it to vector.
            if (fs::exists(fsPath))
            {
                vFiles.push_back(fsPath);
            }
        }
        else
        {
            // If we have a directory as a path then we should
            // add all FILE_DEFAULT_EXTENSION files whose names begins with FILE_DEFAULT_FILENAME
            for (auto& p : fs::directory_iterator(fsPath))
            {
                const fs::path& filepath = p.path();
                if (filepath.has_filename() &&
                    filepath.has_extension() &&
                    filepath.extension().compare(FILE_DEFAULT_EXTENSION))
                {
                    std::string filename = filepath.filename().string();
                    if (filename.find(FILE_DEFAULT_FILENAME) != std::string::npos)
                    {
                        vFiles.push_back(filepath.string());
                    }
                }
            }
        }
    }
    vFiles.shrink_to_fit();
    std::sort(vFiles.begin(), vFiles.end());
    return vFiles;

}
