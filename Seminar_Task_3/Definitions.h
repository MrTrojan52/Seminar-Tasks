//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_DEFINITIONS_H
#define SEMINAR_TASK_3_DEFINITIONS_H

#include <fort.hpp>

#define FILE_DEFAULT_EXTENSION          "txt"
#define FILE_DEFAULT_FILENAME           "task"

#define GREEDY_TASK_DEFAULT_PERCENT     100

#define USE_ALL_ORDERS                  -1

enum etTASK_TYPE
{
    GREEDY_TASK = 0,
    RECURSIVE_TASK,
    TABLE_TASK
};

enum etSORTING_STRATEGY
{
    BASE_SORTING = 0,
    CUSTOM_SORTING
};

enum etTIME_TABLE_COLS
{
    TASK_COL = 0,
    REC_TIME_COL,
    REC_CRIT_COL,
    TBL_TIME_COL,
    TBL_CRIT_COL,
    TIME_DIFF_COL
};


struct Task_OutputData
{
    Task_OutputData(long time, int crit)
    : m_time(time),
      m_crit(crit)
    {

    }

    long m_time;
    int m_crit;
};
#endif //SEMINAR_TASK_3_DEFINITIONS_H
