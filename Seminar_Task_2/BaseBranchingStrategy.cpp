//
// Created by trojan52.
//

#include "BaseBranchingStrategy.h"

VertexInfo BaseBranchingStrategy::Branching(std::vector<VertexInfo> &vVertexes)
{
    int nMin = vVertexes[0].nLowerBound;
    size_t nMinIndex = 0;
    for (size_t i = 1; i < vVertexes.size(); ++i)
    {
        if (vVertexes[i].nLowerBound < nMin)
        {
            nMin = vVertexes[i].nLowerBound;
            nMinIndex = i;
        }
    }
    VertexInfo viRet = vVertexes[nMinIndex];
    std::swap(vVertexes[nMinIndex], vVertexes.back());
    vVertexes.pop_back();
    return viRet;
}
