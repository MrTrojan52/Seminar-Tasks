//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_BASEBRANCHINGSTRATEGY_H
#define SEMINAR_TASK_2_BASEBRANCHINGSTRATEGY_H

#include "IBranchingStrategy.h"

class BaseBranchingStrategy : public IBranchingStrategy
{
    public:
        VertexInfo Branching(std::vector<VertexInfo>& vVertexes) override;
};


#endif //SEMINAR_TASK_2_BASEBRANCHINGSTRATEGY_H
