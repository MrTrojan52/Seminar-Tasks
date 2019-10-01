//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_ILOGGER_H
#define SEMINAR_TASK_2_ILOGGER_H

#include <vector>
#include <string>

class ILogger
{
public:
    virtual void AddHeader(std::string sHeaders) = 0;
    virtual void AddRow(std::vector<std::string> vRow) = 0;
    virtual void PrintData() = 0;
};

#endif //SEMINAR_TASK_2_ILOGGER_H
