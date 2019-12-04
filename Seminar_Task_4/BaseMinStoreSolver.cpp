//
// Created by trojan52.
//

#include <iostream>
#include <algorithm>
#include "BaseMinStoreSolver.h"
#include "FordFulkersonSolver.h"

std::pair<bool, int> CBaseMinStoreSolver::SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data)
{
    std::vector<bool> bStores(Data.nConsumersCount, false);
    int nStoreCap = Data.nMaxFlow;

    pNetwork->SaveNodes();

    for (int i = 0; i < Data.nConsumersCount; ++i)
    {
        if (!bStores[i])
        {
            for (int t = 0; t < Data.nTactsCount - 1; ++t)
            {
                int nFrom = Data.nSuppliersCount * Data.nTactsCount + Data.nSuppliersCount + 1 + Data.nTactsCount * i + t;
                int nTo = nFrom + 1;

                auto pFArc = new CFlowArc(nFrom, nTo, nStoreCap);
                auto pBArc = new CFlowArc(nTo, nFrom, 0);

                pNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
                pNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
            }
        }
    }

    CFordFulkersonSolver BaseAlg;
    bool bHaveSolution = BaseAlg.SolveFlowTask(pNetwork, Data).first;

    pNetwork->RestoreNetwork();

    if (!bHaveSolution)
    {
        std::cerr << "Max flow isn't reached" << std::endl;
        return {false, -1};
    }
    else
    {
        for (int j = 0; j < Data.nConsumersCount; ++j)
        {
            pNetwork->SaveNodes();
            bStores[j] = true;
            for (int i = 0; i < Data.nConsumersCount; ++i)
            {
                if (!bStores[i])
                {
                    for (int t = 0; t < Data.nTactsCount - 1; ++t)
                    {
                        int nFrom = Data.nSuppliersCount * Data.nTactsCount + Data.nSuppliersCount + 1 + Data.nTactsCount * i + t;
                        int nTo = nFrom + 1;

                        auto pFArc = new CFlowArc(nFrom, nTo, nStoreCap);
                        auto pBArc = new CFlowArc(nTo, nFrom, 0);

                        pNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
                        pNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
                    }
                }
            }
            bHaveSolution = BaseAlg.SolveFlowTask(pNetwork, Data).first;
            if (!bHaveSolution)
            {
                bStores[j] = false;
            }
            pNetwork->RestoreNetwork();
        }

        int nCnt = std::count(bStores.begin(), bStores.end(), false);
        return {true , nCnt};
    }
}
