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
        explicit CustomBruteforceStrategy(size_t nW);
        void SetLengths(std::vector<T> vLengths)  override;
        std::vector<T> GetNextLengths() override;

    private:
        size_t m_nW;
        std::vector<T> m_vLengths;
};

template<typename T>
CustomBruteforceStrategy<T>::CustomBruteforceStrategy(size_t nW)
{
    if (nW >= 0 && nW <= 100)
    {
        m_nW = nW;
    }
    else
    {
        throw std::invalid_argument("W should be between 0 and 100");
    }
}

template<typename T>
void CustomBruteforceStrategy<T>::SetLengths(std::vector<T> vLengths)
{
    this->m_vPermutation.clear();
    this->m_vPermutation.resize(vLengths.size());
    std::iota(this->m_vPermutation.begin(), this->m_vPermutation.end(), 0);

    std::sort(this->m_vPermutation.begin(), this->m_vPermutation.end(), [&vLengths](T& l, T& r)
    {
        return vLengths[l] > vLengths[r];
    });
    size_t k = (m_nW * this->m_vPermutation.size()) / 100;
    auto aLastElement = std::next(this->m_vPermutation.begin(), k);

    // This sorting is needed for std::next_permutation
    // because it works with lexicographically ordered sequences
    std::sort(aLastElement, this->m_vPermutation.end());

    m_vLengths = std::move(vLengths);
    this->SetIsDone(false);
}

template<typename T>
std::vector<T> CustomBruteforceStrategy<T>::GetNextLengths()
{
    std::vector<T> vRet;
    if (!this->IsDone() && !this->m_vPermutation.empty())
    {
        size_t k = (m_nW * this->m_vPermutation.size()) / 100;
        auto aLastElement = std::next(this->m_vPermutation.begin(), k);
        vRet = this->m_vPermutation;
        if (k < this->m_vPermutation.size())
        {
            this->SetIsDone(!std::next_permutation(aLastElement, this->m_vPermutation.end()));
        }
        else
        {
            this->SetIsDone(true);
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
