//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_SALESMANTASK_H
#define SEMINAR_TASK_5_SALESMANTASK_H

#include <utility>
#include <vector>
#include <string>

#include "DefaultFactory.h"

namespace TSP
{
    class SalesmanTask
    {
        public:
            SalesmanTask() = default;
            explicit SalesmanTask(std::vector<CCity> vCities);
            void PopulateTaskFromFile(const std::string& sFileName);
            void Solve(int nAlpha = DEFAULT_ALPHA, int nBeta = DEFAULT_BETA,
                       etREDUCTION eReduction = eDEFAULT_REDUCTION);

            void AddCity(CCity newCity)
            {
                m_vCities.push_back(newCity);
            }

            size_t CitiesCount()
            {
                return m_vCities.size();
            }

        private:
            void Greedy();
            [[nodiscard]] SubTaskList Reduction(int nAlpha);
            void Restoration(SubTaskList SubTasks);
            void SetReductionStrategy(etREDUCTION eReduction);

            std::vector<CCity> m_vCities;
            Permutation m_vPermutation;
            etREDUCTION m_eReductionStrategy = eDEFAULT_REDUCTION;
            std::unique_ptr<IReductionStrategy> m_pReductionStrategy;

    };


}


#endif //SEMINAR_TASK_5_SALESMANTASK_H
