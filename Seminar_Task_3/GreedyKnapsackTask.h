//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_GREEDYKNAPSACKTASK_H
#define SEMINAR_TASK_3_GREEDYKNAPSACKTASK_H

#include "BaseKnapsackTask.h"
#include "ISortingStrategy.h"

class GreedyKnapsackTask : public BaseKnapsackTask
{
    public:
        GreedyKnapsackTask(const std::string& sTaskPath, etSORTING_STRATEGY eSortingStrategy);
        void SetSortingStrategy(etSORTING_STRATEGY eStrategy);
        void SetPercent(int nPercent);

    protected:
        void doSolve() override;

    private:
        std::unique_ptr<ISortingStrategy> m_pSortingStrategy;
        etSORTING_STRATEGY m_eSortingStrategy;
        int m_nPercent;
};


#endif //SEMINAR_TASK_3_GREEDYKNAPSACKTASK_H
