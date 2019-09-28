//
// Created by Trojan on 27.09.2019.
//

#ifndef SPECSEM_LAB1_IALGORITHM_H
#define SPECSEM_LAB1_IALGORITHM_H
#include <vector>
#include "IAlgorithmData.h"

template<typename T>
class IAlgorithm
{
public:
    virtual std::vector<T> GetSolution(IAlgorithmData<T>* data) = 0;
};
#endif //SPECSEM_LAB1_IALGORITHM_H
