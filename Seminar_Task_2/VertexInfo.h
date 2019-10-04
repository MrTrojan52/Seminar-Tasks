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

    bool operator==(VertexInfo& rhs)
    {
        bool bEqual = true;
        if ((nUpperBound != rhs.nUpperBound)||
            (nLowerBound != rhs.nLowerBound))
        {
            bEqual = false;
        }

        if (vVertex.size() != rhs.vVertex.size())
        {
            bEqual = false;
        }
        else
        {
            for (size_t i = 0; i < vVertex.size(); ++i)
            {
                if (vVertex[i] != rhs.vVertex[i])
                {
                    bEqual = false;
                    break;
                }
            }
        }

        return bEqual;
    }

    bool operator!=(VertexInfo& rhs)
    {
        return !(*this == rhs);
    }

};

#endif //SEMINAR_TASK_2_VERTEXINFO_H
