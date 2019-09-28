//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_ISTRATEGY_H
#define SPECSEM_LAB1_ISTRATEGY_H

#include <vector>

template<typename T>
class IStrategy
{
    public:
        virtual std::vector<std::vector<T> > GetUpdatedLengths(std::vector<T> vLenghts) = 0;
};
#endif //SPECSEM_LAB1_ISTRATEGY_H
