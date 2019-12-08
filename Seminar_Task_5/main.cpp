#include <iostream>
#include "SalesmanTask.h"

int main()
{
    TSP::SalesmanTask Task;
    Task.PopulateTaskFromFile("../Tests/task_5_01_n38.txt");
    Task.Solve();
    return 0;
}