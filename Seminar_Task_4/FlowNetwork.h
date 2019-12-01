//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FLOWNETWORK_H
#define SEMINAR_TASK_4_FLOWNETWORK_H

#include "FlowNode.h"

class CFlowNetwork
{
    public:
        void AddNode(CFlowNode* pNode)
        {
            m_pNodes.push_back(pNode);
        }

        CFlowNode* GetNodeByIndex(int nIndex)
        {
            return m_pNodes[nIndex];
        }

        int GetNodesCount()
        {
            return m_pNodes.size();
        }

    private:
        std::vector<CFlowNode*> m_pNodes;
};


#endif //SEMINAR_TASK_4_FLOWNETWORK_H
