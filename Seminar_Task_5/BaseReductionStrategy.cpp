//
// Created by trojan52.
//

#include "BaseReductionStrategy.h"
#include "SalesmanTask.h"

SubTaskList CBaseReductionStrategy::Reduction(const std::vector<CCity> &rCities, int nAlpha) const
{
    auto Points = Get2DistantPoints(rCities);
    auto vCenters = GetCenters(rCities,{Points.first, Points.second}, nAlpha);
    ClusterList clusters = GetClusters(rCities, vCenters);

    return GetSubTasks(rCities, clusters);
}

std::pair<int, int> CBaseReductionStrategy::Get2DistantPoints(const std::vector<CCity> &rCities) const
{
    double dMax = -1;
    std::pair<int, int> PointsIndexes;

    int nCitiesCount = rCities.size();

    for (int i = 0; i < (nCitiesCount - 1); ++i)
    {
        for (int j = (i + 1); j < nCitiesCount; ++j)
        {
            double dDiff = rCities[i].DistanceTo(rCities[j]);
            if (dDiff > dMax)
            {
                dMax = dDiff;
                PointsIndexes.first = i;
                PointsIndexes.second = j;
            }
        }
    }
    return PointsIndexes;
}

std::vector<int> CBaseReductionStrategy::GetCenters(const std::vector<CCity>& rCities, std::vector<int> vCenters, int nAlpha) const
{
    while (vCenters.size() < nAlpha)
    {
        double dMax = -1;
        int nFurthestId = INCORRECT_VALUE;

        for (size_t i = 0; i < rCities.size(); ++i)
        {
            double dDiff = 0;
            for (int center : vCenters)
            {
                if (i != center)
                {
                    dDiff += rCities[i].DistanceTo(rCities[center]);
                }
                else
                {
                    dDiff = 0;
                    break;
                }
            }

            if (dDiff > dMax)
            {
                dMax = dDiff;
                nFurthestId = i;
            }
        }

        vCenters.push_back(nFurthestId);
    }

    return vCenters;
}

ClusterList CBaseReductionStrategy::GetClusters(const std::vector<CCity> &rCities, const std::vector<int>& rCenters) const
{
    ClusterList Clusters(rCenters.size());

    for (size_t i = 0; i < rCities.size(); ++i)
    {
        double dMin = std::numeric_limits<double>::max();
        int nNearestCenter = INCORRECT_VALUE;

        for (size_t j = 0; j < rCenters.size(); ++j)
        {
            if (i == rCenters[j])
            {
                dMin = 0;
                nNearestCenter = j;
                break;
            }

            double dDist = rCities[i].DistanceTo(rCities[rCenters[j]]);
            if (dDist < dMin)
            {
                dMin = dDist;
                nNearestCenter = j;
            }
        }
        Clusters[nNearestCenter].push_back(i);
    }

    return Clusters;
}

SubTaskList CBaseReductionStrategy::GetSubTasks(const std::vector<CCity> &rCities, const ClusterList &rClusters) const
{
    SubTaskList SubTasks(new std::vector<SalesmanTask>);
    SubTasks->reserve(rClusters.size());

    for (auto& cluster : rClusters)
    {
        SubTasks->emplace_back(SalesmanTask());
        for (int cityIndex : cluster)
        {
            SubTasks->back().AddCity(rCities[cityIndex]);
        }
    }

    return SubTasks;
}
