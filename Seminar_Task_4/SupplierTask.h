//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_SUPPLIERTASK_H
#define SEMINAR_TASK_4_SUPPLIERTASK_H

#include "Definitions.h"
#include "FordFulkersonSolver.h"

class CSupplierTask
{
    public:
        CSupplierTask()
        : m_nSuppliersCount(-1),
          m_nConsumersCount(-1),
          m_nTactsCount(-1),
          m_nSolution(-1),
          m_nBandwidth(-1),
          m_pSolver(new CFordFulkersonSolver)
        { }

        void PopulateTaskFromFile(const std::string& sFile);
        virtual void SolveTask();
    protected:
        int m_nSuppliersCount;
        int m_nConsumersCount;
        int m_nTactsCount;
        int m_nSolution;
        int m_nBandwidth;
        std::shared_ptr<CFlowNetwork> m_pFlowNetwork;
        std::unique_ptr<IFlowTaskSolver> m_pSolver;

        // Vectors and matrices
        std::vector<int> m_vSuppliersTotalProduct;
        Matrix m_mSuppliersProductPerTact;
        Matrix m_mConsumersUsedProductPerTact;
        SetsList m_slSuppliers;

        // Network vectors
        std::vector<CFlowNetworkNode*> m_vnSuppliersTotal;
        std::vector<CFlowNetworkNode*> m_vnSuppliersPartial;
        std::vector<CFlowNetworkNode*> m_vnConsumersPartial;

        void ClearTaskData();
        void ValidateTask() const;
        void CreateFlowNetwork();
};


#endif //SEMINAR_TASK_4_SUPPLIERTASK_H
