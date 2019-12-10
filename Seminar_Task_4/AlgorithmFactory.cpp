//
// Created by trojan52.
//

#include "AlgorithmFactory.h"
#include "FordFulkersonSolver.h"
#include "EverybodyHasStorageSolver.h"
#include "MinSizeStoreSolver.h"
#include "BaseMinStoreSolver.h"
#include "SortingMinStoreSolver.h"

const CAlgorithmFactory &CAlgorithmFactory::Instance()
{
    static CAlgorithmFactory factory;
    return factory;
}

std::unique_ptr<IFlowTaskSolver> CAlgorithmFactory::GetAlgorithm(etAlgorithm eAlg) const
{
    std::unique_ptr<IFlowTaskSolver> pAlg = nullptr;

    switch(eAlg)
    {
        case eFORDFULKERSON:
            pAlg = std::make_unique<CFordFulkersonSolver>();
            break;

        case eEVERYBODY:
            pAlg = std::make_unique<CEverybodyHasStorageSolver>();
            break;

        case eMINSIZESTORE:
            pAlg = std::make_unique<CMinSizeStoreSolver>();
            break;

        case eBASEMINSTORE:
            pAlg = std::make_unique<CBaseMinStoreSolver>();
            break;

        case eSORTINGMINSTORE:
            pAlg = std::make_unique<CSortingMinStoreSolver>();
            break;

        default:
            break;
    }
    return pAlg;
}
