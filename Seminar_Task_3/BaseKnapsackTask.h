//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_BASEKNAPSACKTASK_H
#define SEMINAR_TASK_3_BASEKNAPSACKTASK_H
#include <vector>
#include <string>

#include "Definitions.h"
#include "DefaultFactory.h"
#include "OrderInfo.h"

class BaseKnapsackTask
{
    public:
        BaseKnapsackTask(const std::string& sTaskPath);
        void SetTasksPath(const std::string& sPath);
        void Solve() { Solve(USE_ALL_ORDERS); };
        void Solve(int k);
        int GetCalculatedProfit() { return m_nCalculatedProfit; }
        std::vector<bool> GetTakenOrders() { return m_vbX;}
        std::vector<Task_OutputData> GetTaskData() { return m_vTaskData; }

    protected:
        virtual void doSolve(int k) = 0;
        virtual void PopulateTaskFromFile(const std::string& sFile);
        virtual void ClearTaskData();

        [[nodiscard]] std::vector<std::string> ExtractFilesFromPath() const;

        int m_nPerfomance;
        size_t m_nNumberOfOrders;
        int m_nCalculatedProfit;
        std::vector<OrderInfo> m_vOrders;
        std::vector<bool> m_vbX;
        std::string m_sTasksPath;
        std::vector<Task_OutputData> m_vTaskData;
};


#endif //SEMINAR_TASK_3_BASEKNAPSACKTASK_H
