//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_CUSTOMBRANCHINGSTRATEGY_H
#define SEMINAR_TASK_2_CUSTOMBRANCHINGSTRATEGY_H

#include "IBranchingStrategy.h"

class CustomBranchingStrategy : public IBranchingStrategy
{
    public:
        VertexInfo Branching(std::vector<VertexInfo>& vVertexes) override;

};


#endif //SEMINAR_TASK_2_CUSTOMBRANCHINGSTRATEGY_H
