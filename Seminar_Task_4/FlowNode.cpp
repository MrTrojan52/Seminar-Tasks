//
// Created by trojan52.
//

#include "FlowNode.h"
#include <algorithm>

void CFlowNode::AddArc(CFlowArc *pFArc, CFlowArc *pBArc)
{
    m_vpForwardArcs.push_back(pFArc);
    m_vpBackwardArcs.push_back(pBArc);

    if (m_bSaveAddition)
    {
        m_vpForwardArcsToDelete.push_back(pFArc);
        m_vpBackwardArcsToDelete.push_back(pBArc);
    }
}

void CFlowNode::ChangeArcWeight(int nIndex, int nVal)
{
    if ((nIndex < m_vpForwardArcs.size()) && (nIndex < m_vpBackwardArcs.size()))
    {
        m_vpForwardArcs[nIndex]->m_nWeight -= nVal;
        m_vpBackwardArcs[nIndex]->m_nWeight += nVal;
    }
    else
    {
        throw std::out_of_range("Not valid index [" + std::to_string(nIndex) + "] for array of size [" + std::to_string(m_vpForwardArcs.size()) + "]");
    }
}

void CFlowNode::RestoreArcs()
{
    m_bSaveAddition = false;

    for (int i = 0; i < m_vpForwardArcsToDelete.size(); ++i)
    {
       for (int j = 0; j < m_vpForwardArcs.size(); ++j)
       {
           if (m_vpForwardArcs[j] == m_vpForwardArcsToDelete[i])
           {
               m_vpForwardArcs.erase(m_vpForwardArcs.begin() + j);
               break;
           }
       }
    }


    for (int i = 0; i < m_vpBackwardArcsToDelete.size(); ++i)
    {
        for (int j = 0; j < m_vpBackwardArcs.size(); ++j)
        {
            if (m_vpBackwardArcs[j] == m_vpBackwardArcsToDelete[i])
            {

                m_vpBackwardArcs.erase(m_vpBackwardArcs.begin() + j);
                break;
            }
        }

    }

    m_vpForwardArcsToDelete.clear();
    m_vpBackwardArcsToDelete.clear();
}
