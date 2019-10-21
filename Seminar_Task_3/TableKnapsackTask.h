//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_TABLEKNAPSACKTASK_H
#define SEMINAR_TASK_3_TABLEKNAPSACKTASK_H

#include <map>

#include "BaseKnapsackTask.h"

typedef std::pair<int, int> wPosition;

class TableKnapsackTask : public BaseKnapsackTask
{
    public:
        TableKnapsackTask()
        : BaseKnapsackTask(),
          m_pPrevious(nullptr),
          m_pNext(nullptr)
        {}
    protected:
        void doSolve() override;

    private:
        void PrepareTaskForSolving();

        std::vector<int> m_vFirstColumn;
        std::vector<int> m_vSecondColumn;
        std::vector<int>* m_pPrevious;
        std::vector<int>* m_pNext;

        std::map<wPosition, std::vector<bool>> m_mXToWPositions;
};


#endif //SEMINAR_TASK_3_TABLEKNAPSACKTASK_H
