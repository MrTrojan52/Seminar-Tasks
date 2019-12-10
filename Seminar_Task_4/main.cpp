#include <iostream>

#include "SupplierTask.h"

#define MANUAL_FILES_SELECTION 1

int main()
{
    #if (MANUAL_FILES_SELECTION)
        std::vector<std::string> vsFiles
        {
            TASK_FILE("task_4_01_n2_m2_T2.txt"),
            //TASK_FILE("task_4_07_n30_m15_T12.txt")
        };
    #else
        std::vector<std::string> vsFiles = ExtractFilesFromPath("");
    #endif

    for (auto& sFile : vsFiles)
    {
        CSupplierTask task(eEVERYBODY);
        task.PopulateTaskFromFile(sFile);
        task.SolveTask();
        std::cout << task.GetSolutionValue() << std::endl;
    }

    return 0;
}