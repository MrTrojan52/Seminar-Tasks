//
// Created by trojan52.
//

#include "DefaultFactory.h"

#include "BaseBranchingStrategy.h"
#include "BaseLowerBoundStrategy.h"
#include "BaseUpperBoundStrategy.h"

const DefaultFactory &DefaultFactory::Instance()
{
    static DefaultFactory factory;
    return factory;
}

std::unique_ptr<IBranchingStrategy> DefaultFactory::GetBranchingStrategy(etBranchingStrategy eStrategy)
{
    std::unique_ptr<IBranchingStrategy> pStrategy = nullptr;

    switch (eStrategy)
    {
        case eBRANCHING_DEFAULT:
            pStrategy = std::make_unique<BaseBranchingStrategy>();
            break;
        case eBRANCHING_CUSTOM:
            // TODO: add custom init
            break;
        default:
            break;
    }

    return pStrategy;
}

std::unique_ptr<ILowerBoundStrategy> DefaultFactory::GetLowerBoundStrategy(etLowerBoundStrategy eStrategy)
{
    std::unique_ptr<ILowerBoundStrategy> pStrategy = nullptr;

    switch (eStrategy)
    {
        case eLOWERBOUND_BASIC:
            pStrategy = std::make_unique<BaseLowerBoundStrategy>();
            break;
        case eLOWERBOUND_CUSTOM:
            // TODO: add custom init
            break;
        default:
            break;
    }

    return pStrategy;
}

std::unique_ptr<IUpperBoundStrategy> DefaultFactory::GetUpperBoundStrategy(etUpperBoundStrategy eStrategy)
{
    std::unique_ptr<IUpperBoundStrategy> pStrategy = nullptr;

    switch (eStrategy)
    {
        case eUPPERBOUND_BASIC:
            pStrategy = std::make_unique<BaseUpperBoundStrategy>();
            break;
        case eUPPERBOUND_CUSTOM:
            // TODO: add custom init
            break;
        default:
            break;
    }

    return pStrategy;
}
