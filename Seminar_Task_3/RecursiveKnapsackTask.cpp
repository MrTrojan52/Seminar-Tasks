//
// Created by trojan52.
//

#include "RecursiveKnapsackTask.h"


void RecursiveKnapsackTask::doSolve(int k)
{
    int nRes = SolveSubTask(k - 1, m_nPerfomance);
    auto it = m_Cache.find(kwPair(k-1, m_nPerfomance));
    if (it != m_Cache.end())
    {
        m_vbX = it->second.m_x;
    }
    else
    {
        throw std::logic_error("Couldn't find x");
    }
    m_nCalculatedProfit = nRes;
}

int RecursiveKnapsackTask::SolveSubTask(int k, int w)
{
    if (!k)
    {
        if (m_vOrders[k].m_nLaborInput <= w)
        {
            zxPair* pzx = &m_Cache[kwPair(k,w)];
            pzx->m_z = m_vOrders[k].m_nProfit;
            pzx->m_x = { true };
            return m_vOrders[k].m_nProfit;
        }
        else
        {
            zxPair* pzx = &m_Cache[kwPair(k,w)];
            pzx->m_z = 0;
            pzx->m_x = { false };
            return 0;
        }
    }

    auto it = m_Cache.find(kwPair(k - 1, w));
    int f1;

    if (it != m_Cache.end())
    {
        f1 = it->second.m_z;
    }
    else
    {
        f1 = SolveSubTask(k - 1, w);
    }

    if (m_vOrders[k].m_nLaborInput > w)
    {
        zxPair* pzx = &m_Cache[kwPair(k,w)];
        pzx->m_z = f1;
        pzx->m_x = m_Cache[kwPair(k - 1, w)].m_x;
        pzx->m_x.push_back(false);
        return f1;
    }
    else
    {
        int f2;
        it = m_Cache.find(kwPair(k - 1, w - m_vOrders[k].m_nLaborInput));
        if (it != m_Cache.end())
        {
            f2 = it->second.m_z + m_vOrders[k].m_nProfit;
        }
        else
        {
            f2 = SolveSubTask(k - 1, w - m_vOrders[k].m_nLaborInput) + m_vOrders[k].m_nProfit;
        }

        if (f1 <= f2)
        {
            zxPair* pzx = &m_Cache[kwPair(k, w)];
            pzx->m_z = f2;
            pzx->m_x = m_Cache[kwPair(k - 1, w - m_vOrders[k].m_nLaborInput)].m_x;
            pzx->m_x.push_back(true);
            return f2;
        }
        else
        {
            zxPair* pzx = &m_Cache[kwPair(k, w)];
            pzx->m_z = f1;
            pzx->m_x = m_Cache[kwPair(k - 1, w)].m_x;
            pzx->m_x.push_back(false);
            return f1;
        }
    }
}
