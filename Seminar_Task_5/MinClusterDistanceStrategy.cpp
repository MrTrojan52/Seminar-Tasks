//
// Created by trojan52.
//

#include "MinClusterDistanceStrategy.h"
#include "Cluster.h"

ClusterList CMinClusterDistanceStrategy::GetClusters(const std::vector<CCity> &rCities, const std::vector<int> &rCenters) const
{
    ClusterList Clusters(rCenters.size());
    for (int i = 0; i < rCenters.size(); ++i)
    {
        Clusters[i] = std::make_shared<Cluster>();
        Clusters[i]->vCitiesIds.push_back(rCenters[i]);
    }

    auto contains_in_centers = [&rCenters](int nIndex) -> bool
                               {
                                    bool bFound = false;
                                    for (int nCenter : rCenters)
                                    {
                                        if (nCenter == nIndex)
                                        {
                                            bFound = true;
                                            break;
                                        }
                                    }
                                   return bFound;
                               };

    for (size_t i = 0; i < rCities.size(); ++i)
    {
        double dMin = std::numeric_limits<double>::max();
        int nNearestCenter = INCORRECT_VALUE;

        if (contains_in_centers(i))
        {
            continue;
        }

        for (size_t j = 0; j < rCenters.size(); ++j)
        {
            double dDist = Clusters[j]->CalcAverageDistanceWithIndex(i, rCities);
            if (dDist < dMin)
            {
                dMin = dDist;
                nNearestCenter = j;
            }
        }
        if (nNearestCenter != INCORRECT_VALUE)
        {
            Clusters[nNearestCenter]->vCitiesIds.push_back(i);
        }
    }

    return Clusters;
}
