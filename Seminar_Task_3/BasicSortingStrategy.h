//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_BASICSORTINGSTRATEGY_H
#define SEMINAR_TASK_3_BASICSORTINGSTRATEGY_H

#include "ISortingStrategy.h"

class BasicSortingStrategy : public ISortingStrategy
{
    public:
        virtual void sort(int nPerf,
                          size_t nSize,
                          std::vector<OrderInfo>& rOrders) override;
};


#endif //SEMINAR_TASK_3_BASICSORTINGSTRATEGY_H
