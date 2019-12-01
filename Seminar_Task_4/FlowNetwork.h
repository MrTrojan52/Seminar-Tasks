//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FLOWNETWORK_H
#define SEMINAR_TASK_4_FLOWNETWORK_H

#include "FlowNode.h"

class CFlowNetwork
{
    public:

        ~CFlowNetwork()
        {
            for (int i = 0; i < m_pNodes.size(); ++i)
            {
                delete m_pNodes[i];
            }
        }

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
