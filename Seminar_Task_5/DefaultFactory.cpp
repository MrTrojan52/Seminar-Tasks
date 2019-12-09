//
// Created by trojan52.
//

#include "DefaultFactory.h"
#include "CenterRecalculationStrategy.h"
#include "MinClusterDistanceStrategy.h"

const CDefaultFactory &CDefaultFactory::Instance()
{
    static CDefaultFactory factory;
    return factory;
}

std::unique_ptr<IReductionStrategy> CDefaultFactory::GetReductionStrategy(etREDUCTION eReduction) const
{
    std::unique_ptr<IReductionStrategy> pStrategy = nullptr;

    switch (eReduction)
    {
        case eDEFAULT_REDUCTION:
            pStrategy = std::make_unique<CBaseReductionStrategy>();
            break;

        case eCENTER_RECALC_REDUCTION:
            pStrategy = std::make_unique<CCenterRecalculationStrategy>();
            break;

        case eMIN_DISTANCE_IN_CLUSTERS:
            pStrategy = std::make_unique<CMinClusterDistanceStrategy>();
            break;

        default:
            break;
    }

    return pStrategy;
}
