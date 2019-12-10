//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_MINSIZESTORESOLVER_H
#define SEMINAR_TASK_4_MINSIZESTORESOLVER_H

#include "IFlowTaskSolver.h"

class CMinSizeStoreSolver : public IFlowTaskSolver
{
    public:
        std::pair<bool, int> SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data) override;

    private:
        bool SolveCapTask(std::shared_ptr<CFlowNetwork>& pNetwork, TaskData& rData, int nStoreCap);
};


#endif //SEMINAR_TASK_4_MINSIZESTORESOLVER_H
