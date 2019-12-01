//
// Created by trojan52.
//

#include "FlowNode.h"

void CFlowNode::AddArc(CFlowArc *pFArc, CFlowArc *pBArc)
{
    m_vpForwardArcs.push_back(pFArc);
    m_vpBackwardArcs.push_back(pBArc);
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
