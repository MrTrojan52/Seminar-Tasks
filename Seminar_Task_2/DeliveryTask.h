//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_DELIVERYTASK_H
#define SEMINAR_TASK_2_DELIVERYTASK_H

#include <string>
#include <vector>
#include <memory>

#include "VertexInfo.h"
#include "Definitions.h"

#include "ILowerBoundStrategy.h"
#include "IUpperBoundStrategy.h"
#include "IBranchingStrategy.h"

class DeliveryTask
{
    public:
        explicit DeliveryTask(
                                etBranchingStrategy eBranching = eBRANCHING_DEFAULT,
                                etLowerBoundStrategy eLower = eLOWERBOUND_BASIC,
                                etUpperBoundStrategy eUpper = eUPPERBOUND_BASIC
                              );
        void SetTasksPath(const std::string& sPath);
        void Solve();
        void SetBranchingStrategy(etBranchingStrategy eBranchingStrategy);
        void SetLowerBoundStrategy(etLowerBoundStrategy eLowerBoundStrategy);
        void SetUpperBoundStrategy(etUpperBoundStrategy eUpperBoundStrategy);
    private:
        [[nodiscard]] std::vector<std::string> ExtractFilesFromPath() const;
        void PopulateTaskFromFile(const std::string& sFile);
        void ClearTaskData();
        void UpdateBounds();
        void UpdateBounds(VertexInfo& rVertex);
        void AddVertexesAfterBranching(VertexInfo& rVertex);
        void ClipVertexes();
        void UpdateRecord(int nUpperBound);
        void DoBoundsAndTrees();

        std::string m_sTasksPath;
        size_t m_nTaskSize;
        std::vector<int> m_vDeadlines;
        nMatrix m_mTimes;
        std::vector<VertexInfo> m_vVertexes;
        size_t m_nCount;
        int m_nUpperRecord;

        std::unique_ptr<ILowerBoundStrategy> m_pLowerBoundStrategy;
        std::unique_ptr<IUpperBoundStrategy> m_pUpperBoundStrategy;
        std::unique_ptr<IBranchingStrategy> m_pBranchingStrategy;

        etBranchingStrategy m_eBranchingStrategy;
        etLowerBoundStrategy m_eLowerBoundStrategy;
        etUpperBoundStrategy m_eUpperBoundStrategy;

};


#endif //SEMINAR_TASK_2_DELIVERYTASK_H
