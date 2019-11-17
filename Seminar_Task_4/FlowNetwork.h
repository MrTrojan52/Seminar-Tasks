//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FLOWNETWORK_H
#define SEMINAR_TASK_4_FLOWNETWORK_H

#include "FlowNetworkNode.h"

class CFlowNetwork
{
    public:
        explicit CFlowNetwork(CFlowNetworkNode* pSource = nullptr, CFlowNetworkNode* pStock = nullptr)
        : m_pSourceNode(pSource),
          m_pStockNode(pStock)
        { }

        void SetSourceNode(CFlowNetworkNode* pSource);

        void SetStockNode(CFlowNetworkNode* pStock);

        CFlowNetworkNode* GetSourceNode();

        CFlowNetworkNode* GetStockNode();

        int GetFlow();
    private:
        CFlowNetworkNode* m_pSourceNode;
        CFlowNetworkNode* m_pStockNode;
};


#endif //SEMINAR_TASK_4_FLOWNETWORK_H
