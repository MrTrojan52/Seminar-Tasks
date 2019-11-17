//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FORDFULKERSONSOLVER_H
#define SEMINAR_TASK_4_FORDFULKERSONSOLVER_H


#include "IFlowTaskSolver.h"

class CFordFulkersonSolver : public IFlowTaskSolver
{
    public:
        int SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork) override;
};


#endif //SEMINAR_TASK_4_FORDFULKERSONSOLVER_H
