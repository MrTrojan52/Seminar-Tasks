//
// Created by trojan52.
//

#include "BasicSortingStrategy.h"
#include <algorithm>
void BasicSortingStrategy::sort(int nPerf,
                                size_t nSize,
                                std::vector<OrderInfo>& rOrders)
{
    std::sort(rOrders.begin(), rOrders.end(),
            [] (OrderInfo& lhs, OrderInfo& rhs) -> bool
            {
                return (lhs.GetLaborRelation() > rhs.GetLaborRelation());
            });
}
