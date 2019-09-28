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
        std::vector<int> GetSolution(IAlgorithmData<T>* data) override;
};

template<typename T>
std::vector<int> GreedyAlgorithm<T>::GetSolution(IAlgorithmData<T>* data)
{
    std::vector<T> vRods;
    T nRodLength = std::get<T>(data->GetDataByAttribute(ATTR_ROD_LENGTH));
    std::vector<T> vLenghts = std::get<std::vector<T> >(data->GetDataByAttribute(ATTR_LENGHTS_ARRAY));
    std::vector<int> vSolution(vLenghts.size(), 0);
    vRods.push_back(nRodLength);
    bool bCutted = false;
    for (size_t i = 0; i < vLenghts.size(); ++i)
    {
        bCutted = false;
        for (size_t j = 0; j < vRods.size(); ++j)
        {
            if (vLenghts[i] <= vRods[j])
            {
                vSolution[i] = j;
                vRods[j] -= vLenghts[i];
                bCutted = true;
                break;
            }
        }
        if (!bCutted)
        {
            vRods.push_back(nRodLength - vLenghts[i]);
            vSolution[i] = vRods.size() - 1;
        }
    }
    return vSolution;
}


#endif //SPECSEM_LAB1_GREEDYALGORITHM_H
