//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_CUSTOMSORTINGSTRATEGY_H
#define SEMINAR_TASK_3_CUSTOMSORTINGSTRATEGY_H

#include "ISortingStrategy.h"

class CustomSortingStrategy : public ISortingStrategy
{
    public:
        virtual void sort(int nPerf,
                          size_t nSize,
                          std::vector<OrderInfo>& rOrders) override;
};


#endif //SEMINAR_TASK_3_CUSTOMSORTINGSTRATEGY_H
