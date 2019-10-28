#include <iostream>
#include <filesystem>

#include "Definitions.h"
#include "GreedyKnapsackTask.h"
#include "RecursiveKnapsackTask.h"
#include "TableKnapsackTask.h"
#include "lib/fort.hpp"


int main() {
    std::string fsPath = std::filesystem::current_path().parent_path().string();
    fsPath += "/Tests/";

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

        for (size_t i = 0; i < taskData.size(); ++i)
        {
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
        for (size_t i = 0; i < TableTaskData.size(); ++i)
        {
            Time_table[i + 1][TBL_TIME_COL] = std::to_string(TableTaskData[i].m_time);
            Time_table[i + 1][TBL_CRIT_COL] = std::to_string(TableTaskData[i].m_crit);
            vTimeDifference[i + 1] = static_cast<double>(vTimeDifference[i] - TableTaskData[i].m_time) / (vTimeDifference[i] + TableTaskData[i].m_time) * 2;
        }
    }


    for (size_t i = 0; i < vTimeDifference.size(); ++i)
    {
        Time_table[i + 1][TIME_DIFF_COL] = std::to_string(vTimeDifference[i]);
    }

    std::cout << Time_table.to_string() << std::endl;

    // Comparing sorting algorithms
    {
        fort::char_table Basic_Table;
        Basic_Table.set_cell_text_align(fort::text_align::center);
        Basic_Table.set_border_style(FT_DOUBLE2_STYLE);
        Basic_Table << fort::header << "Task #";

        std::vector<double> vdPercentages = {0.1, 0.3, 0.5, 0.7, 1.0};

        for (double p : vdPercentages)
        {
            Basic_Table << std::to_string(p);
        }
        Basic_Table << "Difference" << fort::endr;

        std::vector<double> vDifference;


        for (int i = 0; i < vdPercentages.size(); ++i)
        {
            GreedyKnapsackTask basicTask(fsPath, BASE_SORTING);
            basicTask.SetPercent(vdPercentages[i]);
            basicTask.Solve();
            auto taskData = basicTask.GetTaskData();
            for (int j = 0; j < taskData.size(); ++j)
            {
                Basic_Table[j + 1][i + 1] = std::to_string(taskData[j].m_crit);
            }
        }

        std::cout << Basic_Table.to_string() << std::endl;
    }


    return 0;
}