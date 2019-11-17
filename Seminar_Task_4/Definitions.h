//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_DEFINITIONS_H
#define SEMINAR_TASK_4_DEFINITIONS_H

#include <vector>
#include <string>
#include <filesystem>
#include <set>

#define FILE_DEFAULT_EXTENSION          "txt"
#define FILE_DEFAULT_FILENAME           "task"

enum etNodeType
{
    // Probably inconsistent case
    eUNDEFINED = -1,
    eSOURCE = 0,
    eSUPPLIER,
    eSUPPLIER_PARTIAL,
    eCONSUMER_PARTIAL,
    eSTOCK
};

typedef std::vector<std::vector<int>> Matrix;
typedef std::vector<std::set<int>> SetsList;

#define TASK_FILE(file) (\
        std::filesystem::current_path().parent_path().string() + \
        "/Tests/" + file )

std::vector<std::string> ExtractFilesFromPath(const std::string& sPath);


#endif //SEMINAR_TASK_4_DEFINITIONS_H
