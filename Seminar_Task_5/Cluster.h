//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_CLUSTER_H
#define SEMINAR_TASK_5_CLUSTER_H

#include <vector>
#include "Point.h"

namespace TSP
{
    struct Cluster
    {
        std::vector<int> vCitiesIds;
    };

    struct CenteredCluster : public Cluster
    {
        CPoint pCenter;
    };

}

#endif //SEMINAR_TASK_5_CLUSTER_H
