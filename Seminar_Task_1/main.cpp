#include <iostream>
#include "CuttingTask.h"
int main() {
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    CCuttingTask<int> Task(eALGORITHM_GREEDY, eSTRATEGY_CUSTOM_SORTING);
    Task.SetTasksPath(fsPath + "/Tests/task_1_03_n100.txt");
    Task.Solve();
    Task.PrintData();
    return 0;
}