//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_BASELOGGER_H
#define SEMINAR_TASK_2_BASELOGGER_H


#include "ILogger.h"

class BaseLogger : public ILogger
{
public:
    void AddHeader(std::string sHeaders) override;
    void AddRow(std::vector<std::string> vRow) override;

protected:
    std::vector<std::string> m_vHeaders;
    std::vector<std::vector<std::string> > m_vRecords;
};


#endif //SEMINAR_TASK_2_BASELOGGER_H
