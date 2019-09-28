//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H
#define SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H

#include "IStrategy.h"

template<typename T>
class CustomBruteforceStrategy : public IStrategy<T>
{
    public:
        std::vector<std::vector<T> > GetUpdatedLengths(std::vector<T> vLenghts) override;
};

template<typename T>
std::vector<std::vector<T>> CustomBruteforceStrategy<T>::GetUpdatedLengths(std::vector<T> vLenghts) {
    return std::vector<std::vector<T>>();
}

#endif //SPECSEM_LAB1_CUSTOMBRUTEFORCESTRATEGY_H
