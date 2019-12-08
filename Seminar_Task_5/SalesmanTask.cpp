//
// Created by trojan52.
//

#include <fstream>
#include <algorithm>
#include "SalesmanTask.h"

#define ContainsInPermutation(container, nIndex) \
(std::find(container.begin(), container.end(), nIndex) != container.end())

TSP::SalesmanTask::SalesmanTask(std::vector<CCity> vCities)
: m_vCities(std::move(vCities))
{ }

void TSP::SalesmanTask::PopulateTaskFromFile(const std::string &sFileName)
{
    std::ifstream iFile(sFileName);

    if (iFile.is_open())
    {
        int nSize;
        iFile >> nSize;

        int nNum;
        CPoint Location;

        for (int i = 0; i < nSize; ++i)
        {
            iFile >> nNum;
            iFile >> Location;
            m_vCities.emplace_back(nNum, Location);
        }
    }
}

void TSP::SalesmanTask::Solve(int nAlpha, int nBeta, etREDUCTION eReduction)
{
    SetReductionStrategy(eReduction);

    m_eReductionStrategy = eReduction;
    SubTaskList SubTasks;
    if ((m_vCities.size() > nAlpha) && (nBeta > 0))
    {
        SubTasks = Reduction(nAlpha);
        for (auto& task : (*SubTasks))
        {
            if (task.CitiesCount() > MAX_TASK_SIZE_FOR_GREEDY_SOLVE)
            {
                task.Solve(nAlpha, nBeta - 1);
            }
            else
            {
                task.Greedy();
            }
        }
    }
    else
    {
        Greedy();
        return;
    }

    Restoration(SubTasks);
}

TSP::SubTaskList TSP::SalesmanTask::Reduction(int nAlpha)
{
    return m_pReductionStrategy->Reduction(m_vCities, nAlpha);
}

void TSP::SalesmanTask::Restoration(TSP::SubTaskList SubTasks)
{

}

void TSP::SalesmanTask::Greedy()
{
    int nCitiesCount = CitiesCount();

    m_vPermutation.clear();
    m_vPermutation.reserve(nCitiesCount);
    m_vPermutation.push_back(0);

    while (m_vPermutation.size() < nCitiesCount)
    {
        double dMin = std::numeric_limits<double>::max();
        int nIndex = INCORRECT_VALUE;

        int nCurr = m_vPermutation.back();
        for (int i = 0; i < nCitiesCount; ++i)
        {
            if (ContainsInPermutation(m_vPermutation, i))
            {
                // If we found the current index in permutation then
                // go to the next one
                continue;
            }

            double dDist = m_vCities[nCurr].DistanceTo(m_vCities[i]);
            if (dDist < dMin)
            {
                dMin = dDist;
                nIndex = i;
            }
        }
        if (nIndex != INCORRECT_VALUE)
        {
            m_vPermutation.push_back(nIndex);
        }
        else
        {
            throw std::logic_error("Something went wrong!");
        }
    }
}

void SalesmanTask::SetReductionStrategy(etREDUCTION eReduction)
{
    m_eReductionStrategy = eReduction;
    m_pReductionStrategy = CDefaultFactory::Instance().GetReductionStrategy(eReduction);
}
