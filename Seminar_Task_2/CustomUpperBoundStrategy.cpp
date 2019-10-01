//
// Created by trojan52.
//

#include <gmpxx.h>
#include "CustomUpperBoundStrategy.h"

int CustomUpperBoundStrategy::GetUpperBound(const std::vector<int> &vVertex, std::vector<int> &vDeadlines, nMatrix &mTimes)
{

    std::vector<int> vCurrentVertex(vVertex);
    std::vector<int> vMissing = GetMissingVertexes(vCurrentVertex, vDeadlines.size());
    while (!vMissing.empty())
    {
        if (vMissing.size() > 1) {
            int nMin = std::numeric_limits<int>::max();
            int nMinIndex = -1;

            for (size_t i = 0; i < vMissing.size(); ++i) {
                int nCurrent = vCurrentVertex.back();
                vCurrentVertex.push_back(vMissing[i]);
                std::vector<int> vInnerMissing = GetMissingVertexes(vCurrentVertex, vDeadlines.size());
                for (size_t j = 0; j < vInnerMissing.size(); ++j) {
                    if (mTimes[nCurrent][vMissing[i]] + mTimes[vMissing[i]][vInnerMissing[j]] < nMin) {
                        nMin = mTimes[nCurrent][vMissing[i]] + mTimes[vMissing[i]][vInnerMissing[j]];
                        nMinIndex = i * 10 + j;
                    }
                }
                vCurrentVertex.pop_back();
            }
            vCurrentVertex.push_back(vMissing[nMinIndex / 10]);
            std::vector<int> vInner = GetMissingVertexes(vCurrentVertex, vDeadlines.size());
            vCurrentVertex.push_back(vInner[nMinIndex % 10]);
        }
        else
        {
            vCurrentVertex.push_back(vMissing[0]);
        }
        vMissing = GetMissingVertexes(vCurrentVertex, vDeadlines.size());
    }
    return CalculateCriterion(vCurrentVertex, vDeadlines, mTimes).first;
}
