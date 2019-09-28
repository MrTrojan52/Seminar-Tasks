//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_DEFAULTFACTORY_H
#define SPECSEM_LAB1_DEFAULTFACTORY_H

#include "IAlgorithm.h"
#include "GreedyAlgorithm.h"
#include "Definitions.h"

template<typename T>
class DefaultFactory
{
    public:
        static IAlgorithm<T>* getAlgorithmByEnum(etAlgorithm eAlgorithm);
};

template<typename T>
IAlgorithm<T>* DefaultFactory<T>::getAlgorithmByEnum(etAlgorithm eAlgorithm)
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


#endif //SPECSEM_LAB1_DEFAULTFACTORY_H
