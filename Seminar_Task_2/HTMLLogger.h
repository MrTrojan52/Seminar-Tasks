//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_HTMLLOGGER_H
#define SEMINAR_TASK_2_HTMLLOGGER_H


#include "BaseLogger.h"

class HTMLLogger : public BaseLogger
{
public:
    explicit HTMLLogger(const std::string& rFileName);
    void PrintData() override;

private:
    [[nodiscard]] std::string AddHeaders();
    [[nodiscard]] std::string AddRow(std::vector<std::string>& vRow);
    [[nodiscard]] std::string AddValue(std::string& sValue, size_t colspan = 1, size_t rowspan = 1);
    std::string m_sFileName;
};


#endif //SEMINAR_TASK_2_HTMLLOGGER_H
