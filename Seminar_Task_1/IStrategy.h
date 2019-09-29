//
// Created by trojan52.
//

#ifndef SPECSEM_LAB1_ISTRATEGY_H
#define SPECSEM_LAB1_ISTRATEGY_H

#include <vector>

template<typename T>
class IStrategy
{
    public:
        virtual void SetLengths(std::vector<T> vLenghts) = 0;
        virtual bool IsDone() = 0;
        virtual std::vector<T> GetNextLengths() = 0;
};
#endif //SPECSEM_LAB1_ISTRATEGY_H
