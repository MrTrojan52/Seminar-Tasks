#include <iostream>
#include "SalesmanTask.h"

int main()
{
    TSP::SalesmanTask Task;
    Task.PopulateTaskFromFile("../Tests/task_5_01_n38.txt");
    Task.Solve(DEFAULT_ALPHA, DEFAULT_BETA, eDEFAULT_REDUCTION);

    std::cout << Task.GetLen();
    return 0;
}