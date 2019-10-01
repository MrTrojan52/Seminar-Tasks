//
// Created by trojan52.
//

#include "BaseLogger.h"

void BaseLogger::AddHeader(std::string sHeader)
{
    m_vHeaders.push_back(sHeader);
}

void BaseLogger::AddRow(std::vector<std::string> vRow)
{
    m_vRecords.push_back(vRow);
}