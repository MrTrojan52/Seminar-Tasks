#include <iostream>
#include "SalesmanTask.h"
#include "lib/fort.hpp"

int main()
{
    TSP::SalesmanTask Task;
    std::string sFiles[] =
            {
                "../Tests/task_5_01_n38.txt",
                "../Tests/task_5_02_n131.txt",
                "../Tests/task_5_03_n237.txt",
                "../Tests/task_5_04_n662.txt",
                "../Tests/task_5_05_n734.txt",
                "../Tests/task_5_06_n8246.txt"
            };

    fort::char_table Result_table;
    Result_table.set_cell_text_align(fort::text_align::center);
    Result_table.set_border_style(FT_DOUBLE2_STYLE);
    Result_table << fort::header << "Task #" << "Size" << "Base" << "Custom" <<
               "Known optimum" << "Base deviation" << "Custom deviation" << fort::endr;
    int nTaskNum = 0;
    double dBaseDelta = 0.0;
    double dCustomDelta = 0.0;
    for (auto& sFileName : sFiles)
    {
        ++nTaskNum;
        std::cout << "Processing Task #" << nTaskNum << std::endl;
        Task.PopulateTaskFromFile(sFileName);
        int nTaskSize = Task.CitiesCount();
        Task.Solve(DEFAULT_ALPHA, DEFAULT_BETA, eDEFAULT_REDUCTION);
        double dBase = Task.GetLen();

        Task.Solve(DEFAULT_ALPHA, DEFAULT_BETA, eCENTER_RECALC_REDUCTION);
        double dCustom = Task.GetLen();

        double dOptimum = Task.GetKnownOptimum();

        Result_table << nTaskNum << nTaskSize << dBase << dCustom << dOptimum <<
                     (dBase / dOptimum * 100) << (dCustom / dOptimum * 100) << fort::endr;
        dBaseDelta += (dBase - dOptimum) / dOptimum;
        dCustomDelta += (dCustom - dOptimum) / dOptimum;
    }

    std::cout << Result_table.to_string() << std::endl;
    std::cout << "Base delta: " << dBaseDelta << std::endl;
    std::cout << "Custom delta: " << dCustomDelta << std::endl;

    return 0;
}

/*
 ╔════════╤══════╤═════════╤═════════╤═══════════════╤════════════════╤══════════════════╗
║ Task # │ Size │  Base   │ Custom  │ Known optimum │ Base deviation │ Custom deviation ║
╠════════╪══════╪═════════╪═════════╪═══════════════╪════════════════╪══════════════════╣
║   1    │  38  │ 7836.79 │ 7504.33 │     6656      │     117.74     │     112.745      ║
╟────────┼──────┼─────────┼─────────┼───────────────┼────────────────┼──────────────────╢
║   2    │ 131  │ 797.43  │ 801.315 │      564      │    141.388     │     142.077      ║
╟────────┼──────┼─────────┼─────────┼───────────────┼────────────────┼──────────────────╢
║   3    │ 237  │ 1696.47 │ 1613.76 │     1019      │    166.483     │     158.367      ║
╟────────┼──────┼─────────┼─────────┼───────────────┼────────────────┼──────────────────╢
║   4    │ 662  │ 4731.09 │ 4259.94 │     2513      │    188.265     │     169.516      ║
╟────────┼──────┼─────────┼─────────┼───────────────┼────────────────┼──────────────────╢
║   5    │ 734  │ 129123  │ 126657  │     79114     │    163.212     │     160.095      ║
╟────────┼──────┼─────────┼─────────┼───────────────┼────────────────┼──────────────────╢
║   6    │ 8246 │ 363573  │ 357195  │    206171     │    176.345     │     173.252      ║
╚════════╧══════╧═════════╧═════════╧═══════════════╧════════════════╧══════════════════╝

Base delta: 3.53434
Custom delta: 3.16052

 */