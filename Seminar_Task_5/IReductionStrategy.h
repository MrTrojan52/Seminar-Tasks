//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_IREDUCTIONSTRATEGY_H
#define SEMINAR_TASK_5_IREDUCTIONSTRATEGY_H

#include <vector>
#include "Definitions.h"
#include "City.h"

using namespace TSP;

class IReductionStrategy
{
    public:
        [[nodiscard]] virtual SubTaskList Reduction(const std::vector<CCity>& rCities, int nAlpha) const = 0;
};

#endif //SEMINAR_TASK_5_IREDUCTIONSTRATEGY_H
