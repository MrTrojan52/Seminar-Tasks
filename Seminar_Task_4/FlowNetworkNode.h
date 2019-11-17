//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FLOWNETWORKNODE_H
#define SEMINAR_TASK_4_FLOWNETWORKNODE_H

#include "Definitions.h"

struct Saturation
{
    int m_nCapacity;
    int m_nCurrentFlow;

    explicit Saturation(int nCapacity = -1, int nFlow = -1)
    : m_nCapacity(nCapacity),
      m_nCurrentFlow(nFlow)
    { }
};

class CFlowNetworkNode
{
    public:
        explicit CFlowNetworkNode(etNodeType eType = eUNDEFINED)
        : m_eNodeType(eType)
        { }

        etNodeType GetType() { return m_eNodeType; }

        void SetSaturation(int nCapacity, int nFlow = 0);
        int GetCapacity();
        int GetFlow();
        void AddFlow(int nFlow);
        int GetTotalFlow();

        void AddChild(CFlowNetworkNode* pChild, int nCapacity, int nFlow = 0);

    private:
        etNodeType m_eNodeType;
        Saturation m_Saturation;

        std::vector<CFlowNetworkNode*> m_vpChildren;
};


#endif //SEMINAR_TASK_4_FLOWNETWORKNODE_H
