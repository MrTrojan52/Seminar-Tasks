//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_BASICSTRATEGY_H
#define SPECSEM_LAB1_BASICSTRATEGY_H

#include <algorithm>
#include <functional>

#include "AStrategy.h"

template<typename T>
class BasicStrategy : public AStrategy<T>
{
    public:
        void SetLengths(std::vector<T> vLengths)  override;
        std::vector<T> GetNextLengths() override;
};

template<typename T>
void BasicStrategy<T>::SetLengths(std::vector<T> vLengths)
{
    this->m_vPermutation = std::move(vLengths);
    std::sort(this->m_vPermutation.begin(), this->m_vPermutation.end(), std::greater<T>());
    this->SetIsDone(false);
}

template<typename T>
std::vector<T> BasicStrategy<T>::GetNextLengths()
{
    if (!this->IsDone() && !this->m_vPermutation.empty())
    {
        this->SetIsDone(true);
        return this->m_vPermutation;
    }
    else
    {
        return std::vector<T>();
    }
}


#endif //SPECSEM_LAB1_BASICSTRATEGY_H
