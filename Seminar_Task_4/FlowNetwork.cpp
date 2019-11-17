//
// Created by trojan52.
//

#include "FlowNetwork.h"

void CFlowNetwork::SetSourceNode(CFlowNetworkNode *pSource)
{
    m_pSourceNode = pSource;
}

void CFlowNetwork::SetStockNode(CFlowNetworkNode *pStock)
{
    m_pStockNode = pStock;
}

CFlowNetworkNode* CFlowNetwork::GetSourceNode()
{
    return m_pSourceNode;
}

CFlowNetworkNode* CFlowNetwork::GetStockNode()
{
    return m_pStockNode;
}

int CFlowNetwork::GetFlow()
{
    if (m_pSourceNode)
    {
        return m_pSourceNode->GetFlow();
    }
    else
    {
        return -1;
    }
}
