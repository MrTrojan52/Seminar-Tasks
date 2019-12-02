//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_STORESOLVER_H
#define SEMINAR_TASK_4_STORESOLVER_H

#include "IFlowTaskSolver.h"

class CStoreSolver : public IFlowTaskSolver
{
    public:
        std::pair<bool, int> SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data) override;

    private:
        bool SolveCapTask(std::shared_ptr<CFlowNetwork>& pNetwork, TaskData& rData, int nStoreCap);
};


#endif //SEMINAR_TASK_4_STORESOLVER_H
