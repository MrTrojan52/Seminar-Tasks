//
// Created by trojan52.
//

#include <cmath>
#include "GreedyKnapsackTask.h"


GreedyKnapsackTask::GreedyKnapsackTask(const std::string& sTaskPath, etSORTING_STRATEGY eSortingStrategy)
: BaseKnapsackTask(sTaskPath),
  m_dPercent(GREEDY_TASK_DEFAULT_PERCENT)
{
    SetSortingStrategy(eSortingStrategy);
}

void GreedyKnapsackTask::doSolve(int k)
{
    m_pSortingStrategy->sort(m_nPerfomance, m_nNumberOfOrders, m_vOrders);
    int nCapacity = m_nPerfomance;
    m_nCalculatedProfit = 0;
    k  = ceil(m_nNumberOfOrders * m_dPercent);
    for (size_t i = 0; i < k; ++i)
    {
        int nCurrentLabor = m_vOrders[i].m_nLaborInput;
        if (nCapacity - nCurrentLabor >= 0)
        {
            m_vbX[m_vOrders[i].m_nOriginalIndex] = true;
            nCapacity -= nCurrentLabor;
            m_nCalculatedProfit += m_vOrders[i].m_nProfit;
        }
    }
}

void GreedyKnapsackTask::SetSortingStrategy(etSORTING_STRATEGY eStrategy)
{
    m_eSortingStrategy = eStrategy;
    m_pSortingStrategy = DefaultFactory::Instance().GetSortingStrategy(eStrategy);
}