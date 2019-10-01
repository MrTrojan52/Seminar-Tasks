//
// Created by trojan52.
//

#include "BaseUpperBoundStrategy.h"
#include <limits>

int BaseUpperBoundStrategy::GetUpperBound(const std::vector<int>& vVertex, std::vector<int> &vDeadlines, nMatrix &mTimes)
{
    std::vector<int> vMissing = GetMissingVertexes(vVertex, vDeadlines.size());
    std::vector<int> vCurrentVertex(vVertex);
    while (!vMissing.empty())
    {
        int nCurrent = vCurrentVertex.back();
        int nMin = std::numeric_limits<int>::max();
        int nMinIndex = -1;
        for (size_t i = 0; i < vMissing.size(); ++i)
        {
            if (mTimes[nCurrent][vMissing[i]] < nMin)
            {
                nMin = mTimes[nCurrent][vMissing[i]];
                nMinIndex = i;
            }
        }
        vCurrentVertex.push_back(vMissing[nMinIndex]);
        std::swap(vMissing[nMinIndex], vMissing.back());
        vMissing.pop_back();
    }

    return CalculateCriterion(vCurrentVertex, vDeadlines, mTimes).first;
}
