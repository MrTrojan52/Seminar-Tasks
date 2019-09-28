//
// Created by Trojan on 27.09.2019.
//

#ifndef SPECSEM_LAB1_GREEDYALGORITHM_H
#define SPECSEM_LAB1_GREEDYALGORITHM_H


#include "IAlgorithm.h"

template<typename T>
class GreedyAlgorithm : public IAlgorithm<T>
{
    public:
        std::vector<T> GetSolution(IAlgorithmData<T>* data) override;
};

template<typename T>
std::vector<T> GreedyAlgorithm<T>::GetSolution(IAlgorithmData<T>* data)
{
    return std::vector<T>(10,0);
}


#endif //SPECSEM_LAB1_GREEDYALGORITHM_H
