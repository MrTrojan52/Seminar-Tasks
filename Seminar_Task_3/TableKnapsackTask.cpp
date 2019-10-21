//
// Created by trojan52.
//

#include "TableKnapsackTask.h"

void TableKnapsackTask::doSolve()
{
    PrepareTaskForSolving();

    for (int k = 1; k < m_nNumberOfOrders; ++k)
    {
        for (size_t nW = 0; nW <= m_nPerfomance; ++nW)
        {
            int nFirstFunc = (*m_pPrevious)[nW];
            int nSecondFunc = 0;
            if (m_vOrders[k].m_nLaborInput <= nW)
            {
                nSecondFunc = m_vOrders[k].m_nProfit + (*m_pPrevious)[nW - m_vOrders[k].m_nLaborInput];
                if (nFirstFunc <= nSecondFunc)
                {
                    (*m_pNext)[nW] = nSecondFunc;
                    m_mXToWPositions[wPosition(nW, k)] = m_mXToWPositions[wPosition(nW - m_vOrders[k].m_nLaborInput, k - 1)];
                    m_mXToWPositions[wPosition(nW, k)].push_back(true);
                }
                else
                {
                    (*m_pNext)[nW] = nFirstFunc;
                    m_mXToWPositions[wPosition(nW, k)] = m_mXToWPositions[wPosition(nW, k - 1)];
                    m_mXToWPositions[wPosition(nW, k)].push_back(false);
                }
            }
            else
            {
                (*m_pNext)[nW] = nFirstFunc;
                m_mXToWPositions[wPosition(nW, k)] = m_mXToWPositions[wPosition(nW, k - 1)];
                m_mXToWPositions[wPosition(nW, k)].push_back(false);
            }
        }

        std::swap(m_pPrevious, m_pNext);
    }

    auto iterator = m_mXToWPositions.find(wPosition(m_nPerfomance, m_nNumberOfOrders - 1));
    if (iterator != m_mXToWPositions.end())
    {
        m_vbX = iterator->second;
    }
    else
    {
        throw std::logic_error("Something went wrong!");
    }

    m_nCalculatedProfit = (*m_pPrevious)[m_nPerfomance];
}

void TableKnapsackTask::PrepareTaskForSolving()
{
    m_vFirstColumn.resize(m_nPerfomance + 1);
    m_vSecondColumn.resize(m_nPerfomance + 1);
    m_pPrevious = &m_vFirstColumn;
    m_pNext = &m_vSecondColumn;

    for (int nW = 0; nW <= m_nPerfomance; ++nW)
    {
        if (m_vOrders[0].m_nLaborInput <= nW)
        {
            m_vFirstColumn[nW] = m_vOrders[0].m_nProfit;
            m_mXToWPositions[wPosition(nW, 0)] = { true };
        }
        else
        {
            m_vFirstColumn[nW] = 0;
            m_mXToWPositions[wPosition(nW, 0)] = { false };
        }
    }
}
