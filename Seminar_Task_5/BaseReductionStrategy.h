//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_BASEREDUCTIONSTRATEGY_H
#define SEMINAR_TASK_5_BASEREDUCTIONSTRATEGY_H

#include "IReductionStrategy.h"

class CBaseReductionStrategy : public IReductionStrategy
{
    public:
        [[nodiscard]] SubTaskList Reduction(const std::vector<CCity>& rCities, int nAlpha) const override;

    protected:
        [[nodiscard]] std::pair<int, int> Get2DistantPoints(const std::vector<CCity>& rCities) const;
        [[nodiscard]] std::vector<int> GetCenters(const std::vector<CCity>& rCities, std::vector<int> vCenters, int nAlpha) const;
        [[nodiscard]] virtual ClusterList GetClusters(const std::vector<CCity>& rCities, const std::vector<int>& rCenters) const;
        [[nodiscard]] virtual SubTaskList GetSubTasks(const std::vector<CCity>& rCities, const ClusterList& rClusters) const;
};


#endif //SEMINAR_TASK_5_BASEREDUCTIONSTRATEGY_H
