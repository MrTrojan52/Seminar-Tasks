//
// Created by trojan52.
//

#include "AlgorithmFactory.h"
#include "FordFulkersonSolver.h"
#include "StoreSolver.h"

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

        case eSTORE:
            pAlg = std::make_unique<CStoreSolver>();
            break;

        default:
            break;
    }
    return pAlg;
}
