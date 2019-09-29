//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_CUSTOMSORTINGSTRATEGY_H
#define SPECSEM_LAB1_CUSTOMSORTINGSTRATEGY_H

#include <algorithm>

#include "AStrategy.h"

template<typename T>
class CustomSortingStrategy : public AStrategy<T>
{
    public:
        explicit CustomSortingStrategy(size_t nSteps);
        void SetLengths(std::vector<T> vLengths)  override;
        std::vector<T> GetNextLengths() override;

    private:
        size_t m_nMaxSteps;
        size_t m_nCurrentStep;
};

template<typename T>
void CustomSortingStrategy<T>::SetLengths(std::vector<T> vLengths)
{
    this->m_vPermutation = std::move(vLengths);
    this->SetIsDone(false);
    m_nCurrentStep = 0;
}

template<typename T>
std::vector<T> CustomSortingStrategy<T>::GetNextLengths()
{
    if (!this->IsDone() && !this->m_vPermutation.empty())
    {
        std::sort(this->m_vPermutation.begin(), this->m_vPermutation.end(), std::greater<T>());
        double w = static_cast<double>((m_nCurrentStep * 100)) / (m_nMaxSteps);
        int k = (this->m_vPermutation.size() * w) / 100;
        auto aLastElement = std::next(this->m_vPermutation.begin(), k);
        std::sort(aLastElement, this->m_vPermutation.end());
        ++m_nCurrentStep;
        if (m_nCurrentStep >= m_nMaxSteps)
        {
            this->SetIsDone(true);
        }
        return this->m_vPermutation;
    }
    else
    {
        return std::vector<T>();
    }
}

template<typename T>
CustomSortingStrategy<T>::CustomSortingStrategy(size_t nSteps)
: m_nCurrentStep(0)
{
    if (nSteps >= 2)
    {
        m_nMaxSteps = nSteps;
    }
    else
    {
        throw std::invalid_argument("Number of steps for CustomSortingStrategy must be >= 2.");
    }

}

#endif //SPECSEM_LAB1_CUSTOMSORTINGSTRATEGY_H
