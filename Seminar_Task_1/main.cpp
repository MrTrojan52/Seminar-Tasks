#include <iostream>
#include "CuttingTask.h"
int main() {
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    CCuttingTask<int> Task(eALGORITHM_GREEDY, eSTRATEGY_ALL);
    Task.SetTasksPath(fsPath + "/Tests/");
    Task.Solve();
    Task.PrintData();
    return 0;
}