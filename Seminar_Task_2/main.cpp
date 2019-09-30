#include <iostream>
#include <filesystem>

#include "DeliveryTask.h"

int main()
{
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    DeliveryTask Task;
    Task.SetTasksPath(fsPath + "/Tests/task_2_03_n10.txt");
    Task.Solve();
    return 0;
}