#include <iostream>
#include "CuttingTask.h"
int main() {
    CCuttingTask<int> Task(eALGORITHM_GREEDY, eSTRATEGY_CUSTOM_BRUTEFORCE);
    Task.SetTasksPath("/home/trojan52/UNN/Seminar-Tasks/Seminar_Task_1/Tests/task_1_01_n10.txt");
    Task.Solve();
    Task.PrintData();
    return 0;
}