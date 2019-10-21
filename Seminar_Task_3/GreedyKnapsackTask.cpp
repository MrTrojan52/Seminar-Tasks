//
// Created by trojan52.
//

#include "GreedyKnapsackTask.h"


GreedyKnapsackTask::GreedyKnapsackTask(etSORTING_STRATEGY eSortingStrategy)
: m_nPercent(GREEDY_TASK_DEFAULT_PERCENT)
{
    SetSortingStrategy(eSortingStrategy);
}

void GreedyKnapsackTask::doSolve()
{
    m_pSortingStrategy->sort(m_nPerfomance, m_nNumberOfOrders, m_vOrders);
    int nCapacity = m_nPerfomance;
    m_nCalculatedProfit = 0;
    size_t nSteps = std::min(m_nNumberOfOrders, (m_nNumberOfOrders * m_nPercent) / 100);

    for (size_t i = 0; i < nSteps; ++i)
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

void GreedyKnapsackTask::SetPercent(int nPercent)
{
    if (nPercent <= 0 || nPercent > 100)
    {
        nPercent = GREEDY_TASK_DEFAULT_PERCENT;
    }

    m_nPercent = nPercent;
}
