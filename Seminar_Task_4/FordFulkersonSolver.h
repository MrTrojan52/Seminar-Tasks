//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FORDFULKERSONSOLVER_H
#define SEMINAR_TASK_4_FORDFULKERSONSOLVER_H


#include "IFlowTaskSolver.h"

class CFordFulkersonSolver : public IFlowTaskSolver
{
    public:
        std::pair<bool, int> SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data) override;


    private:
        std::vector<CFlowNode*> m_vWay;
        std::vector<int> m_vMarks;
        std::shared_ptr<CFlowNetwork> m_pNetwork;
        int m_nMaxFlow;

        std::vector<CFlowNode*> GetWay(std::vector<int>& vInd, int& rWeight);
        std::vector<CFlowNode*> RecGetWay(std::vector<int>& vInd, int nNum);
};


#endif //SEMINAR_TASK_4_FORDFULKERSONSOLVER_H
