//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_ISORTINGSTRATEGY_H
#define SEMINAR_TASK_3_ISORTINGSTRATEGY_H

#include <vector>
#include "OrderInfo.h"

class ISortingStrategy
{
    public:
        virtual void sort(int nPerf,
                          size_t nSize,
                          std::vector<OrderInfo>& rOrders) = 0;
};

#endif //SEMINAR_TASK_3_ISORTINGSTRATEGY_H
