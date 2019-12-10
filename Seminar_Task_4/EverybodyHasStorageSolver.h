//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_EVERYBODYHASSTORAGESOLVER_H
#define SEMINAR_TASK_4_EVERYBODYHASSTORAGESOLVER_H

#include "IFlowTaskSolver.h"
class CEverybodyHasStorageSolver : public IFlowTaskSolver
{
    public:
        std::pair<bool, int> SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data) override;
};


#endif //SEMINAR_TASK_4_EVERYBODYHASSTORAGESOLVER_H
