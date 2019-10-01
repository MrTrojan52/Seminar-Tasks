//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_ABOUNDSTRATEGY_H
#define SEMINAR_TASK_2_ABOUNDSTRATEGY_H

#include "Definitions.h"

class ABoundStrategy
{
    public:
        [[nodiscard]] std::pair<int, int> CalculateCriterion(const std::vector<int>& vVertex, const std::vector<int>& vDeadlines, const nMatrix& mTimes);
        std::vector<int> GetMissingVertexes(const std::vector<int>& vVertex, int nSize);
};


#endif //SEMINAR_TASK_2_ABOUNDSTRATEGY_H
