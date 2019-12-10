//
// Created by trojan52.
//

#include "EverybodyHasStorageSolver.h"
#include "FordFulkersonSolver.h"

std::pair<bool, int> CEverybodyHasStorageSolver::SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data)
{
    int nU = Data.nU;
    int nStoragesCount = 0;

    pNetwork->SaveNodes();
    for (int i = 0; i < Data.nConsumersCount; ++i)
    {
        for (int t = 0; t < Data.nTactsCount - 1; ++t)
        {
            int nFrom = Data.nSuppliersCount * Data.nTactsCount + Data.nSuppliersCount + 1 + Data.nTactsCount * i + t;
            int nTo = nFrom + 1;

            auto pFArc = new CFlowArc(nFrom, nTo, nU);
            auto pBArc = new CFlowArc(nTo, nFrom, 0);

            pNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
            pNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
            ++nStoragesCount;
        }
    }
    CFordFulkersonSolver alg;
    bool bRes = alg.SolveFlowTask(pNetwork, Data).first;
    pNetwork->RestoreNetwork();

    return {bRes, nStoragesCount};
}
