//
// Created by trojan52.
//

#include <fstream>
#include <algorithm>
#include <numeric>
#include "SalesmanTask.h"

#define ContainsInPermutation(container, nIndex) \
(std::find(container.begin(), container.end(), nIndex) != container.end())

TSP::SalesmanTask::SalesmanTask(std::vector<CCity> vCities)
: m_vCities(std::move(vCities))
{ }

void TSP::SalesmanTask::PopulateTaskFromFile(const std::string &sFileName)
{
    m_vCities.clear();
    ClearData();

    std::ifstream iFile(sFileName);

    if (iFile.is_open())
    {
        int nSize;
        iFile >> nSize;

        iFile >> m_dKnownOptimum;

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
    if ((m_vCities.size() > MAX_TASK_SIZE_FOR_GREEDY_SOLVE) && (nBeta > 0))
    {
        SubTasks = Reduction(nAlpha);
        for (auto& task : (*SubTasks))
        {
            task.Solve(nAlpha, nBeta - 1, eReduction);
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
    auto ExternalPermut = SolveExternalTask(SubTasks);
    int nExternalPermutSize = ExternalPermut->size();

    m_vPermutation.clear();
    m_vPermutation.reserve(CitiesCount());

    int nCurCluster = (*ExternalPermut)[0];
    int nNextCluster = (*ExternalPermut)[1];

    auto* pCurrentSubTask = &(*SubTasks)[nCurCluster];
    auto* pNextSubTask = &(*SubTasks)[nNextCluster];

    auto ClDist = pCurrentSubTask->GetMinDistanceToCluster(*pNextSubTask);

    int nRealIndex = FindCityIndexByNumber(pCurrentSubTask->m_vCities[ClDist.nFirstId].m_nNumber);
    m_vPermutation.push_back(nRealIndex);

    nRealIndex = FindCityIndexByNumber(pNextSubTask->m_vCities[ClDist.nSecondId].m_nNumber);
    m_vPermutation.push_back(nRealIndex);

    int first_cluster_pair[2];
    FillIndexPair(first_cluster_pair, *pCurrentSubTask, ClDist.nFirstId);

    int nEndIndex = ClDist.nFirstId;

    nCurCluster = nNextCluster;

    int nCurrentStartIndex = ClDist.nFirstId;
    int nNextStartIndex = ClDist.nSecondId;

    for (int i = 2; i < nExternalPermutSize; ++i)
    {
        nCurrentStartIndex = nNextStartIndex;
        pCurrentSubTask = &(*SubTasks)[nCurCluster];

        int nCurrentEndIndex = INCORRECT_VALUE;
        int pCurrentPair[2];
        FillIndexPair(pCurrentPair, *pCurrentSubTask, nCurrentStartIndex);

        double dMin = std::numeric_limits<double>::max();
        nNextCluster = (*ExternalPermut)[i];
        pNextSubTask = &(*SubTasks)[nNextCluster];

        for (int pairId : pCurrentPair)
        {
            for (int j = 0; j < pNextSubTask->CitiesCount(); ++j)
            {
                double dDist = pCurrentSubTask->m_vCities[pairId].DistanceTo(pNextSubTask->m_vCities[j]);
                if (dDist < dMin)
                {
                    dMin = dDist;
                    nCurrentEndIndex = pairId;
                    nNextStartIndex = j;
                }
            }
        }

        AddLoopToTaskPermutation((*SubTasks)[nCurCluster], nCurrentStartIndex, nCurrentEndIndex);
        m_vPermutation.push_back(FindCityIndexByNumber(pNextSubTask->m_vCities[nNextStartIndex].m_nNumber));
        nCurCluster = nNextCluster;
    }

    pCurrentSubTask = &(*SubTasks)[nCurCluster];
    nCurrentStartIndex = nNextStartIndex;
    int nCurrentEndIndex = INCORRECT_VALUE;

    int pCurrentPair[2];
    FillIndexPair(pCurrentPair, *pCurrentSubTask, nCurrentStartIndex);

    double dMin = std::numeric_limits<double>::max();
    nNextCluster = (*ExternalPermut)[0];
    pNextSubTask = &(*SubTasks)[nNextCluster];

    for (int currPairId : pCurrentPair)
    {
        for (int firstPairId : first_cluster_pair)
        {
            double dDiff = pCurrentSubTask->m_vCities[currPairId].DistanceTo(pNextSubTask->m_vCities[firstPairId]);
            if (dDiff < dMin)
            {
                dMin = dDiff;
                nCurrentEndIndex = currPairId;
                nNextStartIndex = firstPairId;
            }
        }
    }

    AddLoopToTaskPermutation((*SubTasks)[nCurCluster], nCurrentStartIndex, nCurrentEndIndex);
    m_vPermutation.push_back(FindCityIndexByNumber(pNextSubTask->m_vCities[nNextStartIndex].m_nNumber));


    AddLoopToTaskPermutation((*SubTasks)[nNextCluster], nNextStartIndex, nEndIndex);
}

void SalesmanTask::FillIndexPair(int pIndexes[2], const SalesmanTask &rTask, int nIndex) const
{
    int nIndexInPerm = FindPermutationIndexInTask(rTask, nIndex);

    pIndexes[0] = (nIndexInPerm - 1) < 0 ?
                  rTask.m_vPermutation[rTask.CitiesCount() - 1] :
                  rTask.m_vPermutation[nIndexInPerm - 1];

    pIndexes[1] = (nIndexInPerm + 1 ) >= rTask.CitiesCount() ?
                  rTask.m_vPermutation[0] :
                  rTask.m_vPermutation[nIndexInPerm + 1];
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

std::shared_ptr<Permutation> SalesmanTask::SolveExternalTask(const SubTaskList &rSubTasks)
{
    int nSubTasksCount = rSubTasks->size();
    Permutation ClustersPermut;
    ClustersPermut.resize(nSubTasksCount);

    PointList Centers;
    Centers.reserve(nSubTasksCount);

    // Create an initial permutation
    // values from 0 to (Count of SubTasks - 1)
    std::iota(ClustersPermut.begin(), ClustersPermut.end(), 0);

    for (int i = 0; i < nSubTasksCount; ++i)
    {
        Centers.emplace_back((*rSubTasks)[i].CenterPoint());
    }

    double dMinWay = std::numeric_limits<double>::max();

    std::shared_ptr<Permutation> pPermutation(new Permutation);
    pPermutation->reserve(nSubTasksCount);

    double dWayLen = 0.0;

    do
    {
        dWayLen = 0.0;
        int nCurrentClusterId = ClustersPermut[0];
        int nNextClusterId = INCORRECT_VALUE;
        for (int i = 1; i < nSubTasksCount; ++i)
        {
            nNextClusterId = ClustersPermut[i];
            dWayLen += Centers[nCurrentClusterId].DistanceTo(Centers[nNextClusterId]);
            nCurrentClusterId = nNextClusterId;
        }

        dWayLen += Centers[nCurrentClusterId].DistanceTo(Centers[ClustersPermut[0]]);

        if (dWayLen < dMinWay)
        {
            dMinWay = dWayLen;
            *pPermutation = ClustersPermut;
        }

    } while(std::next_permutation(ClustersPermut.begin(), ClustersPermut.end()));

    return pPermutation;
}

CPoint SalesmanTask::CenterPoint()
{
    double sumX = 0.0;
    double sumY = 0.0;

    for (auto city : m_vCities)
    {
        sumX += city.m_Location.m_X;
        sumY += city.m_Location.m_Y;
    }

    int nCitiesCount = CitiesCount();
    return CPoint((sumX / nCitiesCount), (sumY / nCitiesCount));
}

ClusterDistance SalesmanTask::GetMinDistanceToCluster(const SalesmanTask &rhs) const
{
    double dMin = std::numeric_limits<double>::max();
    int nFirst = INCORRECT_VALUE;
    int nSecond = INCORRECT_VALUE;

    ClusterDistance retDist;
    for (size_t i = 0; i < CitiesCount(); ++i)
    {
        for (size_t j = 0; j < rhs.CitiesCount(); ++j)
        {
            double dDist = m_vCities[i].DistanceTo(rhs.m_vCities[j]);
            if (dDist < dMin)
            {
                dMin = dDist;
                retDist.nFirstId = i;
                retDist.nSecondId = j;
            }
        }
    }
    retDist.Distance = dMin;

    return retDist;
}

int SalesmanTask::FindCityIndexByNumber(int nNumber) const
{
    int nIndex = INCORRECT_VALUE;
    for (size_t i = 0; i < m_vCities.size(); ++i)
    {
        if (m_vCities[i].m_nNumber == nNumber)
        {
            nIndex = i;
            break;
        }
    }
    return nIndex;
}

int TSP::SalesmanTask::FindPermutationIndexInTask(const SalesmanTask &rTask, int index)
{
    int nIndex = INCORRECT_VALUE;
    for (int i = 0; i < rTask.CitiesCount(); ++i)
    {
        if (rTask.m_vPermutation[i] == index)
        {
            nIndex = i;
            break;
        }

    }
    return nIndex;
}

void TSP::SalesmanTask::AddLoopToTaskPermutation(SalesmanTask &rTask, int nIndexStart, int nIndexEnd){
    if (rTask.CitiesCount() == 1)
    {
        return;
    }

    int nPermIndex = FindPermutationIndexInTask(rTask, nIndexStart);

    int nIndexNext = (nPermIndex + 1) >= rTask.CitiesCount() ?
                     rTask.m_vPermutation[0] :
                     rTask.m_vPermutation[nPermIndex + 1];

    int nStep = (nIndexNext == nIndexEnd) ? -1 : 1;

    nIndexNext = rTask.m_vPermutation[nPermIndex];

    do
    {
        nPermIndex += nStep;
        if (nPermIndex == rTask.CitiesCount())
        {
            nPermIndex = 0;
        }

        if (nPermIndex == -1)
        {
            nPermIndex = rTask.CitiesCount() - 1;
        }

        nIndexNext = rTask.m_vPermutation[nPermIndex];
        m_vPermutation.push_back(FindCityIndexByNumber(rTask.m_vCities[nIndexNext].m_nNumber));
    } while (nIndexNext != nIndexEnd);
}

double SalesmanTask::GetLen() const
{
    double dLen = 0.0;

    for (size_t i = 0; i < m_vPermutation.size() - 1; ++i)
    {
        int nCurrent = m_vPermutation[i];
        int nNext = m_vPermutation[i + 1];

        dLen += m_vCities[nCurrent].DistanceTo(m_vCities[nNext]);
    }

    dLen += m_vCities[m_vPermutation.back()].DistanceTo(m_vCities[m_vPermutation[0]]);
    return dLen;
}

void SalesmanTask::ClearData()
{
    m_vPermutation.clear();
    m_dKnownOptimum = 0.0;
}
