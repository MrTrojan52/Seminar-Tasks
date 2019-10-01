//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_BASELOWERBOUNDSTRATEGY_H
#define SEMINAR_TASK_2_BASELOWERBOUNDSTRATEGY_H

#include "ILowerBoundStrategy.h"
#include "ABoundStrategy.h"

class BaseLowerBoundStrategy : public ILowerBoundStrategy, public ABoundStrategy
{
    public:
        int GetLowerBound(const std::vector<int>& vVertex, std::vector<int>& vDeadlines, nMatrix& mTimes) override;
};


#endif //SEMINAR_TASK_2_BASELOWERBOUNDSTRATEGY_H
