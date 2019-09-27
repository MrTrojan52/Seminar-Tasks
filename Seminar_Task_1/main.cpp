#include <iostream>
#include "CuttingTask.h"
int main() {
    CCuttingTask<int> Task(nullptr);
    Task.SetTasksPath("/home/trojan52/UNN/Seminar-Tasks/Seminar_Task_1/Tests/task_1_01_n10.txt");
    Task.Solve();
    return 0;
}