//
// Created by trojan52.
//

#ifndef SPECSEM_LAB1_BASELOGGER_H
#define SPECSEM_LAB1_BASELOGGER_H

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


#endif //SPECSEM_LAB1_BASELOGGER_H
