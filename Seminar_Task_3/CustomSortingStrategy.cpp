//
// Created by trojan52.
//

#include <algorithm>
#include "CustomSortingStrategy.h"

void CustomSortingStrategy::sort(int nPerf, size_t nSize, std::vector<OrderInfo> &rOrders)
{
    std::sort(rOrders.begin(), rOrders.end(),
              [] (OrderInfo& lhs, OrderInfo& rhs) -> bool
              {
                  return ((lhs.GetLaborRelation() > rhs.GetLaborRelation()) &&
                         (lhs.m_nProfit > rhs.m_nProfit));
              });
}
