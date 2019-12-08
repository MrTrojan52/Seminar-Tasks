//
// Created by trojan52.
//

#include "DefaultFactory.h"
#include "BaseReductionStrategy.h"

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

        default:
            break;
    }

    return pStrategy;
}
