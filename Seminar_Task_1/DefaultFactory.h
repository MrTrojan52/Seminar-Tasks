//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_DEFAULTFACTORY_H
#define SPECSEM_LAB1_DEFAULTFACTORY_H

#include <memory>

#include "IAlgorithm.h"
#include "IStrategy.h"
#include "BasicStrategy.h"
#include "CustomSortingStrategy.h"
#include "CustomBruteforceStrategy.h"
#include "GreedyAlgorithm.h"
#include "Definitions.h"

template<typename T>
class DefaultFactory
{
    public:
        [[nodiscard]] static std::unique_ptr<IAlgorithm<T>> GetAlgorithmByEnum(etAlgorithm eAlgorithm);
        [[nodiscard]] static std::unique_ptr<IStrategy<T>>  GetStrategyByEnum(etStrategy eStrategy);
};

template<typename T>
std::unique_ptr<IAlgorithm<T>> DefaultFactory<T>::GetAlgorithmByEnum(etAlgorithm eAlgorithm)
{
    std::unique_ptr<IAlgorithm<T>> pAlgorithm = nullptr;
    switch(eAlgorithm)
    {
        case eALGORITHM_GREEDY:
            pAlgorithm.reset(new GreedyAlgorithm<T>);
            break;
        default:
            break;
    }
    return pAlgorithm;
}

template<typename T>
std::unique_ptr<IStrategy<T>> DefaultFactory<T>::GetStrategyByEnum(etStrategy eStrategy)
{
    std::unique_ptr<IStrategy<T>> pStrategy = nullptr;
    switch(eStrategy)
    {
        case eSTRATEGY_BASIC:
            pStrategy.reset(new BasicStrategy<T>);
            break;
        case eSTRATEGY_CUSTOM_SORTING:
            pStrategy.reset(new CustomSortingStrategy<T>(DEFAULT_STEPS_FOR_SORTING));
            break;
        case eSTRATEGY_CUSTOM_BRUTEFORCE:
            pStrategy.reset(new CustomBruteforceStrategy<T>(DEFAULT_W_FOR_BRUTEFORCE));
            break;
        case eSTRATEGY_AS_IS:
        case eSTRATEGY_ALL:
        default:
            break;
    }
    return pStrategy;
}


#endif //SPECSEM_LAB1_DEFAULTFACTORY_H
