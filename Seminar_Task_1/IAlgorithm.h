//
// Created by Trojan on 27.09.2019.
//

#ifndef SPECSEM_LAB1_IALGORITHM_H
#define SPECSEM_LAB1_IALGORITHM_H
#include <vector>
#include "IAlgorithmData.h"

template<typename AlgDataType, typename SolutionType = std::vector<int>>
class IAlgorithm
{
public:
    virtual SolutionType GetSolution(std::unique_ptr<IAlgorithmData<AlgDataType>> data) = 0;
};
#endif //SPECSEM_LAB1_IALGORITHM_H
