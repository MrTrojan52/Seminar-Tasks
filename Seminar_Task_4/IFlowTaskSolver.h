//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_IFLOWTASKSOLVER_H
#define SEMINAR_TASK_4_IFLOWTASKSOLVER_H


#include <memory>
#include "FlowNetwork.h"

class IFlowTaskSolver
{
    public:
       virtual std::pair<bool, int> SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data) = 0;
};
#endif //SEMINAR_TASK_4_IFLOWTASKSOLVER_H
