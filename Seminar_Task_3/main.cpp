#include <iostream>
#include <filesystem>

#include "Definitions.h"
#include "GreedyKnapsackTask.h"

int main() {
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    GreedyKnapsackTask task(BASE_SORTING);
    task.SetTasksPath(fsPath + "/Tests/");
    task.Solve();
    std::cout << task.GetCalculatedProfit() << std::endl;
    return 0;
}