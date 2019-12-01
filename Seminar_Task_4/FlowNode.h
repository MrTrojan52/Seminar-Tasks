//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FLOWNODE_H
#define SEMINAR_TASK_4_FLOWNODE_H

#include "FlowArc.h"
#include "Definitions.h"

class CFlowNode
{
    public:

        explicit CFlowNode(etNodeType eType = eUNDEFINED)
        : m_eNodeType(eType)
        { }

        void AddArc(CFlowArc* pFArc, CFlowArc* pBArc);

        void ChangeArcWeight(int nIndex, int nVal);

        std::vector<CFlowArc*>& GetForwardArcs()
        {
            return m_vpForwardArcs;
        }

        std::vector<CFlowArc*>& GetBackwardArcs()
        {
            return m_vpBackwardArcs;
        }

        etNodeType GetNodeType()
        {
            return m_eNodeType;
        }

    private:
        std::vector<CFlowArc*> m_vpForwardArcs;
        std::vector<CFlowArc*> m_vpBackwardArcs;

        etNodeType m_eNodeType;
};


#endif //SEMINAR_TASK_4_FLOWNODE_H
