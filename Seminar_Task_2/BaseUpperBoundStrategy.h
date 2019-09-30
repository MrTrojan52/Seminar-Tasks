//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_BASEUPPERBOUNDSTRATEGY_H
#define SEMINAR_TASK_2_BASEUPPERBOUNDSTRATEGY_H

#include "IUpperBoundStrategy.h"

class BaseUpperBoundStrategy : public IUpperBoundStrategy
{
    public:
        int GetUpperBound(std::vector<int>& vVertex, std::vector<int>& vDeadlines, nMatrix& mTimes) override;
};


#endif //SEMINAR_TASK_2_BASEUPPERBOUNDSTRATEGY_H
