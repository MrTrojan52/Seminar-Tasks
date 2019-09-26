#include <iostream>
#include "CuttingTask.h"
int main() {
    CCuttingTask Task(nullptr);
    Task.SetTasksPath("Tasks/file.txt");
    Task.Solve();
    return 0;
}