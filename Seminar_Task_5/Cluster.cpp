//
// Created by trojan52.
//

#include "Cluster.h"

double TSP::Cluster::CalcAverageDistance(const std::vector<CCity> &rCities)
{
    double dTotalDist = 0.0;
    for (int i = 0; i < vCitiesIds.size() - 1; ++i)
    {
        for (int j = i + 1; j < vCitiesIds.size(); ++j)
        {
            dTotalDist += rCities[vCitiesIds[i]].DistanceTo(rCities[vCitiesIds[j]]);
        }
    }
    dAvgDistance = dTotalDist / vCitiesIds.size();

    return dAvgDistance;
}

double TSP::Cluster::CalcAverageDistanceWithIndex(int nAddedIndex, const std::vector<CCity> &rCities)
{
    vCitiesIds.push_back(nAddedIndex);

    dAvgDistance = CalcAverageDistance(rCities);

    vCitiesIds.pop_back();

    return dAvgDistance;
}

