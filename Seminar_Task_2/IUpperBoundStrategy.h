//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_IUPPERBOUNDSTRATEGY_H
#define SEMINAR_TASK_2_IUPPERBOUNDSTRATEGY_H

#include <vector>

#include "Definitions.h"

class IUpperBoundStrategy
{
    public:
        virtual int GetUpperBound(const std::vector<int>& vVertex, std::vector<int>& vDeadlines, nMatrix& mTimes) = 0;
};


#endif //SEMINAR_TASK_2_IUPPERBOUNDSTRATEGY_H
