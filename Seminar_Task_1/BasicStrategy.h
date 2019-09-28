//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_BASICSTRATEGY_H
#define SPECSEM_LAB1_BASICSTRATEGY_H

#include <algorithm>
#include <functional>

#include "IStrategy.h"

template<typename T>
class BasicStrategy : public IStrategy<T>
{
    public:
        std::vector<std::vector<T> > GetUpdatedLengths(std::vector<T> vLenghts) override;
};

template<typename T>
std::vector<std::vector<T> > BasicStrategy<T>::GetUpdatedLengths(std::vector<T> vLenghts) {
    std::sort(vLenghts.begin(), vLenghts.end(), std::greater<T>());
    return { vLenghts };
}


#endif //SPECSEM_LAB1_BASICSTRATEGY_H
