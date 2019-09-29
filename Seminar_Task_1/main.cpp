#include <iostream>
#include "CuttingTask.h"
int main() {
    CCuttingTask<int> Task(eALGORITHM_GREEDY, eSTRATEGY_BASIC);
    Task.SetTasksPath("/home/trojan52/UNN/Seminar-Tasks/Seminar_Task_1/Tests/");
    Task.Solve();
    Task.PrintData();
    return 0;
}