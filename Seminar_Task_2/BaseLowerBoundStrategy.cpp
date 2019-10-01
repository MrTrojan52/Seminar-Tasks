//
// Created by trojan52.
//

#include "BaseLowerBoundStrategy.h"

int BaseLowerBoundStrategy::GetLowerBound(const std::vector<int>& vVertex, std::vector<int> &vDeadlines, nMatrix &mTimes)
{
    auto [nCriterion, nTime] = CalculateCriterion(vVertex, vDeadlines, mTimes);

    std::vector<int> vMissing = GetMissingVertexes(vVertex, vDeadlines.size());
    for (int nMissing : vMissing)
    {
        if (nTime + mTimes[vVertex.back()][nMissing] > vDeadlines[nMissing - 1])
        {
            ++nCriterion;
        }
    }
    return nCriterion;
}
