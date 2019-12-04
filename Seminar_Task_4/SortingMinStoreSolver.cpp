//
// Created by trojan52.
//

#include "SortingMinStoreSolver.h"
#include "FordFulkersonSolver.h"

std::pair<bool, int> CSortingMinStoreSolver::SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data)
{
    std::vector<int> vDiffs(Data.nConsumersCount);
    std::vector<int> vIndexes(Data.nConsumersCount);

    std::vector<bool> bStores(Data.nConsumersCount, false);
    int nStoreCap = Data.nMaxFlow;


    for (int i = 0; i < Data.nConsumersCount; ++i)
    {
        vIndexes[i] = i;
        int nMax = -1;
        int nMin = std::numeric_limits<int>::max();

        for (int t = 0; t < Data.nTactsCount; ++t)
        {
            int nCurrentEl = (*(Data.m_mConsumersUsedProductPerTact))[i][t];
            if (nCurrentEl > nMax)
            {
                nMax = nCurrentEl;
            }

            if (nCurrentEl < nMin)
            {
                nMin = nCurrentEl;
            }
        }

        vDiffs[i] = nMax - nMin;
    }

    for (int i = 0; i < Data.nConsumersCount - 1; ++i)
    {
        bool bFound = false;
        for (int j = i; j < Data.nConsumersCount - i - 1; ++j)
        {
            if (vDiffs[j] > vDiffs[j + 1])
            {
                bFound = true;
                std::swap(vDiffs[j], vDiffs[j + 1]);
                std::swap(vIndexes[j], vIndexes[j + 1]);
            }
        }
        if (!bFound)
        {
            break;
        }
    }

    for (int j = 0; j < Data.nConsumersCount; ++j)
    {
        pNetwork->SaveNodes();
        bStores[vIndexes[j]] = true;
        for (int i = 0; i < Data.nConsumersCount; ++i)
        {
            if (!bStores[vIndexes[i]])
            {
                for (int t = 0; t < Data.nTactsCount - 1; ++t)
                {
                    int nFrom = Data.nSuppliersCount * Data.nTactsCount + Data.nSuppliersCount + 1 + Data.nTactsCount * vIndexes[i] + t;
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

        if (!bHaveSolution)
        {
            bStores[vIndexes[j]] = false;
        }

        pNetwork->RestoreNetwork();
    }

    int nCnt = 0;

    for (int i = 0; i < Data.nConsumersCount; ++i)
    {
        if (!bStores[vIndexes[i]])
        {
            ++nCnt;
        }
    }

    return { true, nCnt};
}
