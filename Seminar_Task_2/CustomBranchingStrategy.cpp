//
// Created by trojan52.
//

#include "CustomBranchingStrategy.h"

VertexInfo CustomBranchingStrategy::Branching(std::vector<VertexInfo>& vVertexes)
{
    int nMinDiff = vVertexes[0].nUpperBound - vVertexes[0].nLowerBound;
    size_t nMinIndex = 0;

    for (size_t i = 0; i < vVertexes.size(); ++i)
    {
        int nDiff = vVertexes[i].nUpperBound - vVertexes[i].nLowerBound;
        if (nDiff < nMinDiff)
        {
            nMinDiff = nDiff;
            nMinIndex = i;
        }
    }

    VertexInfo viRet = vVertexes[nMinIndex];
    std::swap(vVertexes[nMinIndex], vVertexes.back());
    vVertexes.pop_back();
    return viRet;
}
