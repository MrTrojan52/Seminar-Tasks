//
// Created by trojan52.
//

#ifndef SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H
#define SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "AStrategy.h"

template<typename T>
class CustomBruteforceStrategy : public AStrategy<T>
{
    public:
        explicit CustomBruteforceStrategy(size_t nMaxSteps, size_t nRepeats);
        void SetLengths(std::vector<T> vLengths)  override;
        std::vector<T> GetNextLengths() override;

    private:
        size_t m_nMaxSteps;
        size_t m_nMaxRepeats;
        size_t m_nCurrentStep;
        size_t m_nCurrentRepeat;
        std::vector<T> m_vLengths;
};

template<typename T>
CustomBruteforceStrategy<T>::CustomBruteforceStrategy(size_t nMaxSteps, size_t nRepeats)
: m_nCurrentStep(0),
  m_nCurrentRepeat(0)
{
    if ((nMaxSteps >= 2) && (nRepeats >= 1))
    {
        m_nMaxSteps = nMaxSteps;
        m_nMaxRepeats = nRepeats;
    }
    else
    {
        throw std::invalid_argument("Steps count must be >= 2; Repeat count must be >= 1");
    }
}

template<typename T>
void CustomBruteforceStrategy<T>::SetLengths(std::vector<T> vLengths)
{
    this->m_vPermutation.clear();
    this->m_vPermutation.resize(vLengths.size());
    std::iota(this->m_vPermutation.begin(), this->m_vPermutation.end(), 0);

    m_vLengths = std::move(vLengths);
    this->SetIsDone(false);

    m_nCurrentStep = 0;
    m_nCurrentRepeat = 0;
}

template<typename T>
std::vector<T> CustomBruteforceStrategy<T>::GetNextLengths()
{
    std::vector<T> vRet;
    std::sort(this->m_vPermutation.begin(), this->m_vPermutation.end(),
            [this](int l, int r)
            {
                return (this->m_vLengths[l] > this->m_vLengths[r]);
            }
            );
    if (!this->IsDone() && !this->m_vPermutation.empty())
    {
        double dW = static_cast<double>((m_nCurrentStep * 100)) / (m_nMaxSteps);
        size_t k = (dW * this->m_vPermutation.size()) / 100;
        auto aLastElement = std::next(this->m_vPermutation.begin(), k);
        std::random_shuffle(aLastElement, this->m_vPermutation.end());
        vRet = this->m_vPermutation;
        ++m_nCurrentRepeat;
        if (m_nCurrentRepeat >= m_nMaxRepeats)
        {
            ++m_nCurrentStep;
            m_nCurrentRepeat = 0;
            if (m_nCurrentStep >= m_nMaxSteps)
            {
                this->SetIsDone(true);
            }
        }
    }

    if (!vRet.empty())
    {
        for (size_t i = 0; i < vRet.size(); ++i)
        {
            vRet[i] = m_vLengths[vRet[i]];
        }
    }
    return vRet;
}

#endif //SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H
