//
// Created by trojan52.
//

#ifndef SPECSEM_LAB1_ASTRATEGY_H
#define SPECSEM_LAB1_ASTRATEGY_H

#include "IStrategy.h"

template<typename T>
class AStrategy : public IStrategy<T>
{
    public:
        AStrategy();
        void SetIsDone(bool bIsDone);
        bool IsDone() override;

    protected:
        bool m_bIsDone;
        std::vector<T> m_vPermutation;
};

template<typename T>
AStrategy<T>::AStrategy()
: m_bIsDone(false)
{

}

template<typename T>
void AStrategy<T>::SetIsDone(bool bIsDone)
{
    m_bIsDone = bIsDone;
}

template<typename T>
bool AStrategy<T>::IsDone()
{
    return m_bIsDone;
}

#endif //SPECSEM_LAB1_ASTRATEGY_H
