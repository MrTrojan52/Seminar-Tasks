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
       virtual int SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, int nMaxFlow) = 0;
};
#endif //SEMINAR_TASK_4_IFLOWTASKSOLVER_H
