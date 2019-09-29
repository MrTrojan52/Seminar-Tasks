//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H
#define SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "IStrategy.h"

template<typename T>
class CustomBruteforceStrategy : public IStrategy<T>
{
    public:
        explicit CustomBruteforceStrategy(size_t nW);
        std::vector<std::vector<T> > GetUpdatedLengths(std::vector<T> vLenghts) override;

    private:
        size_t m_nW;
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
std::vector<std::vector<T>> CustomBruteforceStrategy<T>::GetUpdatedLengths(std::vector<T> vLengths) {
    std::vector<std::vector<T>> vvRetLengths;
    std::vector<int> vPermutation(vLengths.size());
    std::iota(vPermutation.begin(), vPermutation.end(), 0);

    size_t k = (m_nW * vLengths.size()) / 100;


    std::sort(vPermutation.begin(), vPermutation.end(), [&vLengths](T& l, T& r)
    {
        return vLengths[l] > vLengths[r];
    });
    auto aLastElement = std::next(vPermutation.begin(), k);

    if (k < vLengths.size())
    {
        while(std::next_permutation(aLastElement, vPermutation.end()))
        {
            std::vector<T> vRes(vLengths.size());
            for (size_t i = 0; i < vRes.size(); ++i)
            {
                vRes[i] = vLengths[vPermutation[i]];
            }
            vvRetLengths.push_back(vRes);
        }
    }
    return vvRetLengths;
}

#endif //SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H
