//
// Created by trojan52.
//

#include "DefaultFactory.h"
#include "BasicSortingStrategy.h"
#include "CustomSortingStrategy.h"

const DefaultFactory& DefaultFactory::Instance()
{
    static DefaultFactory factory;
    return factory;
}

std::unique_ptr<ISortingStrategy> DefaultFactory::GetSortingStrategy(etSORTING_STRATEGY eStrategy) const
{
    std::unique_ptr<ISortingStrategy> pStrategy = nullptr;

    switch(eStrategy)
    {
        case BASE_SORTING:
            pStrategy = std::make_unique<BasicSortingStrategy>();
            break;

        case CUSTOM_SORTING:
            pStrategy = std::make_unique<CustomSortingStrategy>();
            break;

        default:
            break;
    }
    return pStrategy;
}


