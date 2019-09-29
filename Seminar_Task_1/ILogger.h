//
// Created by trojan52.
//

#ifndef SPECSEM_LAB1_ILOGGER_H
#define SPECSEM_LAB1_ILOGGER_H

#include <vector>
#include <string>

class ILogger
{
    public:
        virtual void AddHeader(std::string sHeaders) = 0;
        virtual void AddRow(std::vector<std::string> vRow) = 0;
        virtual void PrintData() = 0;
};

#endif //SPECSEM_LAB1_ILOGGER_H
