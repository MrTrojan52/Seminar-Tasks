//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_IBRANCHINGSTRATEGY_H
#define SEMINAR_TASK_2_IBRANCHINGSTRATEGY_H

#include <vector>
#include "VertexInfo.h"

class IBranchingStrategy
{
    public:
        virtual VertexInfo Branching(std::vector<VertexInfo>& vVertexes) = 0;
};

#endif //SEMINAR_TASK_2_IBRANCHINGSTRATEGY_H
