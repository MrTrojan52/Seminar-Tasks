//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_ILOWERBOUNDSTRATEGY_H
#define SEMINAR_TASK_2_ILOWERBOUNDSTRATEGY_H

#include <vector>

#include "Definitions.h"

class ILowerBoundStrategy
{
    public:
        virtual int GetLowerBound(const std::vector<int>& vVertex, std::vector<int>& vDeadlines, nMatrix& mTimes) = 0;
};
#endif //SEMINAR_TASK_2_ILOWERBOUNDSTRATEGY_H
