#include <iostream>
#include <filesystem>

#include "DeliveryTask.h"

int main()
{
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    DeliveryTask Task(eBRANCHING_CUSTOM);
    Task.SetTasksPath(fsPath + "/Tests/");
    Task.Solve();
    Task.PrintData();
    return 0;
}