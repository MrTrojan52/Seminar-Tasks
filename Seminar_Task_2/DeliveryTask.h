//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_DELIVERYTASK_H
#define SEMINAR_TASK_2_DELIVERYTASK_H

#include <string>
#include <vector>

#include "VertexInfo.h"

class DeliveryTask
{
    public:
        DeliveryTask() = default;
        void SetTasksPath(const std::string& sPath);
        void Solve();

    private:
        [[nodiscard]] std::vector<std::string> ExtractFilesFromPath() const;
        void PopulateTaskFromFile(const std::string& sFile);
        void ClearTaskData();

        std::string m_sTasksPath;
        size_t m_nTaskSize;
        std::vector<int> m_vDeadlines;
        std::vector<std::vector<int>> m_mTimes;
        std::vector<VertexInfo> m_vVertexes;
};


#endif //SEMINAR_TASK_2_DELIVERYTASK_H
