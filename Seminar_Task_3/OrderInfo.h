//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_ORDERINFO_H
#define SEMINAR_TASK_3_ORDERINFO_H

struct OrderInfo
{
    explicit OrderInfo(int nLabor = -1, int nProfit = -1, int nIndex = -1)
    : m_nLaborInput(nLabor),
      m_nProfit(nProfit),
      m_nOriginalIndex(nIndex)
    {}

    [[nodiscard]] double GetProfitRelation() const
    {
        return (static_cast<double>(m_nProfit) / m_nLaborInput);
    }

    [[nodiscard]] double GetLaborRelation() const
    {
        return (static_cast<double>(m_nLaborInput) / m_nProfit);
    }

    int m_nLaborInput;
    int m_nProfit;
    int m_nOriginalIndex;
};

#endif //SEMINAR_TASK_3_ORDERINFO_H
