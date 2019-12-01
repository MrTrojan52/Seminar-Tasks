//
// Created by trojan52.
//

#include "FordFulkersonSolver.h"
#include <limits>
int CFordFulkersonSolver::SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, int nMaxFlow)
{
    m_pNetwork = pNetwork;
    m_nMaxFlow = 0;
    m_vWay.clear();

    while (true)
    {
        int nWeight = std::numeric_limits<int>::max();
        int nCalcMaxFlow = 0;
        std::vector<int> vIndexes;

        m_vMarks.clear();
        m_vMarks.resize(pNetwork->GetNodesCount());

        m_vWay = GetWay(vIndexes, nWeight);

        if (m_vWay.empty())
        {
            nCalcMaxFlow = 0;
            int idT = m_pNetwork->GetNodesCount() - 1;
            std::vector<CFlowArc*>& rArcs = m_pNetwork->GetNodeByIndex(idT)->GetForwardArcs();
            for (auto& arc : rArcs)
            {
                nCalcMaxFlow += arc->m_nWeight;
            }


                return nCalcMaxFlow;
        }
        else
        {
            nCalcMaxFlow = 0;
            for (int i = 0; i < m_vWay.size() - 1; ++i)
            {
                m_vWay[i]->ChangeArcWeight(vIndexes[i], nWeight);
            }

            m_nMaxFlow = nCalcMaxFlow;
        }
    }
}


std::vector<CFlowNode*> CFordFulkersonSolver::GetWay(std::vector<int>& vInd, int &rWeight)
{
    rWeight = 0;
    for (int i = 0; i < m_pNetwork->GetNodeByIndex(0)->GetForwardArcs().size(); ++i)
    {
        std::vector<CFlowArc*>& rArcs = m_pNetwork->GetNodeByIndex(0)->GetForwardArcs();
        if (rArcs[i]->m_nWeight > 0)
        {
            m_vWay.clear();
            m_vWay.push_back(m_pNetwork->GetNodeByIndex(0));
            m_vMarks[0] = 1;
            vInd.push_back(i);
            m_vWay.push_back(m_pNetwork->GetNodeByIndex(i + 1));
            m_vMarks[i + 1] = 1;
            RecGetWay(vInd, i + 1);
            if (m_vWay.back()->GetNodeType() == eSTOCK)
            {
                rWeight = std::numeric_limits<int>::max();
                for (int j = 0; j < m_vWay.size() - 1; ++j)
                {
                    int nW = m_vWay[j]->GetForwardArcs()[vInd[j]]->m_nWeight;
                    if (nW < rWeight)
                    {
                        rWeight = nW;
                    }
                }
                return m_vWay;
            }
            vInd.pop_back();
        }
    }

    return { };
}

std::vector<CFlowNode*> CFordFulkersonSolver::RecGetWay(std::vector<int> &vInd, int nNum)
{
    if (m_vWay.back()->GetNodeType() == eSTOCK)
    {
        return m_vWay;
    }
    else
    {
        std::vector<CFlowArc*>& rArcs = m_pNetwork->GetNodeByIndex(nNum)->GetForwardArcs();

        for (int i = 0; i < rArcs.size(); ++i)
        {
            if ((rArcs[i]->m_nWeight > 0) && (m_vMarks[rArcs[i]->m_nTo] == 0))
            {
                m_vWay.push_back(m_pNetwork->GetNodeByIndex(rArcs[i]->m_nTo));

                m_vMarks[rArcs[i]->m_nTo] = 1;
                vInd.push_back(i);
                RecGetWay(vInd, rArcs[i]->m_nTo);
                if (m_vWay.back()->GetNodeType() == eSTOCK)
                {
                    return m_vWay;
                }
                m_vWay.pop_back();
                vInd.pop_back();
            }
        }
    }
    return m_vWay;
}
