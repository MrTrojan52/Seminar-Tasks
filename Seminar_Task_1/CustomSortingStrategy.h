//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_CUSTOMSORTINGSTRATEGY_H
#define SPECSEM_LAB1_CUSTOMSORTINGSTRATEGY_H

#include "AStrategy.h"

template<typename T>
class CustomSortingStrategy : public AStrategy<T>
{
    public:
        void SetLengths(std::vector<T> vLenghts) override;
};

template<typename T>
void CustomSortingStrategy<T>::SetLengths(std::vector<T> vLenghts) {
    this->SetIsDone(true);
}

#endif //SPECSEM_LAB1_CUSTOMSORTINGSTRATEGY_H
