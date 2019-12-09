//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_CLUSTER_H
#define SEMINAR_TASK_5_CLUSTER_H

#include <vector>
#include "City.h"

namespace TSP
{
    struct Cluster
    {
        double CalcAverageDistance(const std::vector<CCity>& rCities);
        double CalcAverageDistanceWithIndex(int nAddedIndex, const std::vector<CCity>& rCities);
        std::vector<int> vCitiesIds;
        CPoint pCenter;
        double dAvgDistance;
    };

}

#endif //SEMINAR_TASK_5_CLUSTER_H
