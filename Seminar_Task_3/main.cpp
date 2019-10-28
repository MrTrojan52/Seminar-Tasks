#include <iostream>
#include <filesystem>

#include "Definitions.h"
#include "GreedyKnapsackTask.h"
#include "RecursiveKnapsackTask.h"
#include "TableKnapsackTask.h"
#include "lib/fort.hpp"

#define DISABLE_NON_GREEDY

//#define DISABLE_GREEDY

int main() {
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    fsPath += "/Tests/";
#ifndef DISABLE_NON_GREEDY
    {
        fort::char_table Time_table;
        Time_table.set_cell_text_align(fort::text_align::center);
        Time_table.set_border_style(FT_DOUBLE2_STYLE);
        Time_table << fort::header << "Task #" << "Recursive time (mcs)" << "Recursive crit" <<
                   "Table time (mcs)" << "Table crit" << "Time difference" << fort::endr;

        std::vector<double> vTimeDifference;

        {
            RecursiveKnapsackTask RecursiveTask(fsPath);
            RecursiveTask.Solve();
            auto taskData = RecursiveTask.GetTaskData();
            vTimeDifference.resize(taskData.size());

            for (size_t i = 0; i < taskData.size(); ++i) {
                // Need to fill first column
                Time_table[i + 1][TASK_COL] = std::to_string(i + 1);

                Time_table[i + 1][REC_TIME_COL] = std::to_string(taskData[i].m_time);
                vTimeDifference[i + 1] = taskData[i].m_time;
                Time_table[i + 1][REC_CRIT_COL] = std::to_string(taskData[i].m_crit);
            }
        }


        {
            TableKnapsackTask TableTask(fsPath);
            TableTask.Solve();
            auto TableTaskData = TableTask.GetTaskData();
            for (size_t i = 0; i < TableTaskData.size(); ++i) {
                Time_table[i + 1][TBL_TIME_COL] = std::to_string(TableTaskData[i].m_time);
                Time_table[i + 1][TBL_CRIT_COL] = std::to_string(TableTaskData[i].m_crit);
                vTimeDifference[i + 1] = static_cast<double>(vTimeDifference[i] - TableTaskData[i].m_time) /
                                         (vTimeDifference[i] + TableTaskData[i].m_time) * 2;
            }
        }


        for (size_t i = 0; i < vTimeDifference.size(); ++i) {
            Time_table[i + 1][TIME_DIFF_COL] = std::to_string(vTimeDifference[i]);
        }

        std::cout << Time_table.to_string() << std::endl;
    }
#endif

#ifndef DISABLE_GREEDY
    // Comparing sorting algorithms
    std::vector<double> vdPercentages = {0.1, 0.3, 0.5, 0.7, 1.0};
    std::vector<std::vector<double>> vvDifference(vdPercentages.size());
    // BASIC STRATEGY
    {
        fort::char_table Basic_Table;
        Basic_Table.set_cell_text_align(fort::text_align::center);
        Basic_Table.set_border_style(FT_DOUBLE2_STYLE);
        Basic_Table << fort::header << "Task #";



        for (double p : vdPercentages)
        {
            Basic_Table << std::to_string(p);
        }
        Basic_Table << fort::endr;

        size_t nTaskSize = 0;
        for (int i = 0; i < vdPercentages.size(); ++i)
        {
            GreedyKnapsackTask basicTask(fsPath, BASE_SORTING);
            basicTask.SetPercent(vdPercentages[i]);
            basicTask.Solve();
            auto taskData = basicTask.GetTaskData();
            nTaskSize = taskData.size();
            vvDifference[i].resize(nTaskSize);
            for (int j = 0; j < nTaskSize; ++j)
            {
                Basic_Table[j + 1][i + 1] = std::to_string(taskData[j].m_crit);
                vvDifference[i][j] = taskData[j].m_crit;
            }
        }

        for (size_t i = 0; i < nTaskSize; ++i)
        {
            Basic_Table[i + 1][TASK_COL] = std::to_string(i + 1);
        }
        std::cout << "BASIC SORTING" << std::endl;
        std::cout << Basic_Table.to_string() << std::endl;
    }

    // MY SORTING STRATEGY
    {
        fort::char_table Sorting_Table;
        Sorting_Table.set_cell_text_align(fort::text_align::center);
        Sorting_Table.set_border_style(FT_DOUBLE2_STYLE);
        Sorting_Table << fort::header << "Task #";



        for (double p : vdPercentages)
        {
            Sorting_Table << std::to_string(p);
        }
        Sorting_Table << fort::endr;

        size_t nTaskSize = 0;
        for (int i = 0; i < vdPercentages.size(); ++i)
        {
            GreedyKnapsackTask customTask(fsPath, CUSTOM_SORTING);
            customTask.SetPercent(vdPercentages[i]);
            customTask.Solve();
            auto taskData = customTask.GetTaskData();
            nTaskSize = taskData.size();
            for (int j = 0; j < nTaskSize; ++j)
            {
                Sorting_Table[j + 1][i + 1] = std::to_string(taskData[j].m_crit);
                vvDifference[i][j] = (vvDifference[i][j] - taskData[j].m_crit) / vvDifference[i][j];
            }
        }

        for (size_t i = 0; i < nTaskSize; ++i)
        {
            Sorting_Table[i + 1][TASK_COL] = std::to_string(i + 1);
        }
        std::cout << "CUSTOM SORTING" << std::endl;
        std::cout << Sorting_Table.to_string() << std::endl;
    }

    // CRIT DIFFERENCES (basic - custom) / basic
    {
        fort::char_table Diff_Table;
        Diff_Table.set_cell_text_align(fort::text_align::center);
        Diff_Table.set_border_style(FT_DOUBLE2_STYLE);
        Diff_Table << fort::header << "Task #";



        for (double p : vdPercentages)
        {
            Diff_Table << std::to_string(p);
        }
        Diff_Table << fort::endr;

        for (size_t i = 0; i < vvDifference.size(); ++i)
        {
            for (size_t j = 0; j < vvDifference[i].size(); ++j)
            {
                Diff_Table[j + 1][i + 1] = std::to_string(vvDifference[i][j]);
            }
        }

        for (size_t i = 0; i < vvDifference[0].size(); ++i)
        {
            Diff_Table[i + 1][TASK_COL] = std::to_string(i + 1);
        }

        std::cout << "DIFFERENCES TABLE" << std::endl;
        std::cout << Diff_Table.to_string() << std::endl;
    }
#endif

    return 0;
}