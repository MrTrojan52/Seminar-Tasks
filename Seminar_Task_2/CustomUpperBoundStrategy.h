//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_CUSTOMUPPERBOUNDSTRATEGY_H
#define SEMINAR_TASK_2_CUSTOMUPPERBOUNDSTRATEGY_H

#include "IUpperBoundStrategy.h"
#include "ABoundStrategy.h"

class CustomUpperBoundStrategy : public IUpperBoundStrategy, public ABoundStrategy
{
    public:
        int GetUpperBound(const std::vector<int>& vVertex, std::vector<int>& vDeadlines, nMatrix& mTimes) override;
};


#endif //SEMINAR_TASK_2_CUSTOMUPPERBOUNDSTRATEGY_H
