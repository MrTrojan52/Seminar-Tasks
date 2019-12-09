//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_MINCLUSTERDISTANCESTRATEGY_H
#define SEMINAR_TASK_5_MINCLUSTERDISTANCESTRATEGY_H

#include "BaseReductionStrategy.h"

class CMinClusterDistanceStrategy : public CBaseReductionStrategy
{
    public:
        [[nodiscard]] ClusterList GetClusters(const std::vector<CCity>& rCities, const std::vector<int>& rCenters) const override;
};


#endif //SEMINAR_TASK_5_MINCLUSTERDISTANCESTRATEGY_H
