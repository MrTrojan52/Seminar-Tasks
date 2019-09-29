#include <iostream>
#include "CuttingTask.h"
int main() {
    CCuttingTask<int> Task(eALGORITHM_GREEDY, eSTRATEGY_CUSTOM_SORTING);
    Task.SetTasksPath("/home/trojan52/UNN/Seminar-Tasks/Seminar_Task_1/Tests/task_1_03_n100.txt");
    Task.Solve();
    Task.PrintData();
    return 0;
}