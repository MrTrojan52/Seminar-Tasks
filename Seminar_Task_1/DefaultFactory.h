//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_DEFAULTFACTORY_H
#define SPECSEM_LAB1_DEFAULTFACTORY_H

#include "IAlgorithm.h"
#include "IStrategy.h"
#include "BasicStrategy.h"
#include "CustomBruteforceStrategy.h"
#include "GreedyAlgorithm.h"
#include "Definitions.h"

template<typename T>
class DefaultFactory
{
    public:
        [[nodiscard]] static IAlgorithm<T>* GetAlgorithmByEnum(etAlgorithm eAlgorithm);
        [[nodiscard]] static IStrategy<T>* GetStrategyByEnum(etStrategy eStrategy);
};

template<typename T>
IAlgorithm<T>* DefaultFactory<T>::GetAlgorithmByEnum(etAlgorithm eAlgorithm)
{
    IAlgorithm<T>* pAlgorithm = nullptr;
    switch(eAlgorithm)
    {
        case eALGORITHM_GREEDY:
            pAlgorithm = new GreedyAlgorithm<T>;
            break;
        default:
            break;
    }
    return pAlgorithm;
}

template<typename T>
IStrategy<T>* DefaultFactory<T>::GetStrategyByEnum(etStrategy eStrategy)
{
    IStrategy<T>* pStrategy = nullptr;
    switch(eStrategy)
    {
        case eSTRATEGY_BASIC:
            pStrategy = new BasicStrategy<T>;
            break;
        case eSTRATEGY_CUSTOM_SORTING:
            //TODO: return First strategy
            break;
        case eSTRATEGY_CUSTOM_BRUTEFORCE:
            pStrategy = new CustomBruteforceStrategy<T>(DEFAULT_W_FOR_BRUTEFORCE);
            break;
        case eSTRATEGY_AS_IS:
        case eSTRATEGY_ALL:
        default:
            break;
    }
    return pStrategy;
}


#endif //SPECSEM_LAB1_DEFAULTFACTORY_H
