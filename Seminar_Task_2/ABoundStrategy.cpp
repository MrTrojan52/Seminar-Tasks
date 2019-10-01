//
// Created by trojan52.
//

#include <algorithm>
#include "ABoundStrategy.h"

std::pair<int, int> ABoundStrategy::CalculateCriterion(const std::vector<int>& vVertex, const std::vector<int> &vDeadlines, const nMatrix &mTimes)
{
    int nCriterion = 0;
    int nTime = mTimes[0][vVertex[0]];
    if (nTime > vDeadlines[vVertex[0] - 1])
    {
        ++nCriterion;
    }

    for (size_t i = 0; i < vVertex.size() - 1; ++i)
    {
        nTime += mTimes[vVertex[i]][vVertex[i + 1]];
        if (nTime > vDeadlines[vVertex[i + 1] - 1])
        {
            ++nCriterion;
        }
    }
    return std::make_pair(nCriterion, nTime);
}

std::vector<int> ABoundStrategy::GetMissingVertexes(const std::vector<int>& vVertex, int nSize)
{
    std::vector<int> vMissing;
    for (size_t i = 0; i < nSize; ++i)
    {
        if (std::find(vVertex.begin(), vVertex.end(), (i + 1)) == vVertex.end())
        {
            vMissing.push_back(i + 1);
        }
    }
    return vMissing;
}
