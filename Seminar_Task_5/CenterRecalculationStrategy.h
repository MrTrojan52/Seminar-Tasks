//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_CENTERRECALCULATIONSTRATEGY_H
#define SEMINAR_TASK_5_CENTERRECALCULATIONSTRATEGY_H

#include "BaseReductionStrategy.h"

class CCenterRecalculationStrategy : public CBaseReductionStrategy
{
    protected:
        [[nodiscard]] CPoint CenterPoint(const std::vector<int>& vIndexes, const std::vector<CCity>& rCities) const;
        [[nodiscard]] ClusterList GetClusters(const std::vector<CCity>& rCities, const std::vector<int>& rCenters) const override;
};


#endif //SEMINAR_TASK_5_CENTERRECALCULATIONSTRATEGY_H
