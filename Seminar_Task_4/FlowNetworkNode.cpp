//
// Created by trojan52.
//

#include <numeric>
#include "FlowNetworkNode.h"

void CFlowNetworkNode::SetSaturation(int nCapacity, int nFlow)
{
    m_Saturation.m_nCapacity = nCapacity;
    m_Saturation.m_nCurrentFlow = nFlow;
}

int CFlowNetworkNode::GetCapacity()
{
    return m_Saturation.m_nCapacity;
}

int CFlowNetworkNode::GetFlow()
{
    return m_Saturation.m_nCurrentFlow;
}

void CFlowNetworkNode::AddFlow(int nFlow)
{
    m_Saturation.m_nCapacity -= nFlow;
    if (m_Saturation.m_nCapacity < 0)
    {
        throw std::invalid_argument("Capacity = 0!");
    }
    m_Saturation.m_nCurrentFlow += nFlow;
}

int CFlowNetworkNode::GetTotalFlow()
{
    auto sumFlow = [](int sum, CFlowNetworkNode* pNode) { return sum + pNode->m_Saturation.m_nCurrentFlow; };
    return std::accumulate(m_vpChildren.begin(), m_vpChildren.end(), 0, sumFlow);
}

void CFlowNetworkNode::AddChild(CFlowNetworkNode *pChild, int nCapacity, int nFlow)
{
    m_vpChildren.push_back(pChild);
    m_vpChildren.back()->SetSaturation(nCapacity, nFlow);
}



