//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_VERTEXINFO_H
#define SEMINAR_TASK_2_VERTEXINFO_H

#include <vector>

struct VertexInfo
{
    std::vector<int> vVertex;
    int nLowerBound;
    int nUpperBound;

    explicit VertexInfo(std::vector<int> p = {}, int nLB = -1, int nUB = -1)
    : vVertex(std::move(p)),
      nLowerBound(nLB),
      nUpperBound(nUB)
    { }

    [[nodiscard]] bool IsBoundsEqual() const
    {
        return (nLowerBound == nUpperBound);
    };
};

#endif //SEMINAR_TASK_2_VERTEXINFO_H
