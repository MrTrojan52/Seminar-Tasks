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
    struct ClusterDistance
    {
        explicit ClusterDistance(double dist = 0, int nFirst = INCORRECT_VALUE, int nSecond = INCORRECT_VALUE)
        : Distance(dist),
          nFirstId(nFirst),
          nSecondId(nSecond)
        { }

        double Distance;
        int nFirstId;
        int nSecondId;
    };


    class SalesmanTask
    {
        public:
            SalesmanTask() = default;
            explicit SalesmanTask(std::vector<CCity> vCities);
            void PopulateTaskFromFile(const std::string& sFileName);
            void Solve(int nAlpha = DEFAULT_ALPHA, int nBeta = DEFAULT_BETA,
                       etREDUCTION eReduction = eDEFAULT_REDUCTION);

            etREDUCTION GetReductionType()
            {
                return m_eReductionStrategy;
            }

            void AddCity(CCity newCity)
            {
                m_vCities.push_back(newCity);
            }

            [[nodiscard]] size_t CitiesCount() const
            {
                return m_vCities.size();
            }

            [[nodiscard]] double GetLen() const;

            double GetKnownOptimum()
            {
                return m_dKnownOptimum;
            }

        private:
            void Greedy();
            [[nodiscard]] SubTaskList Reduction(int nAlpha);
            void Restoration(SubTaskList SubTasks);
            void SetReductionStrategy(etREDUCTION eReduction);
            [[nodiscard]] std::shared_ptr<Permutation> SolveExternalTask(const SubTaskList& rSubTasks);
            [[nodiscard]] CPoint CenterPoint();
            [[nodiscard]] ClusterDistance GetMinDistanceToCluster(const SalesmanTask& rhs) const;
            [[nodiscard]] int FindCityIndexByNumber(int nNumber) const;
            static int FindPermutationIndexInTask(const SalesmanTask& rTask, int index);
            void FillIndexPair(int pIndexes[2], const SalesmanTask& rTask, int nIndex) const;
            void AddLoopToTaskPermutation(SalesmanTask& rTask, int nIndexStart, int nIndexEnd);
            void ClearData();

            std::vector<CCity> m_vCities;
            Permutation m_vPermutation;
            etREDUCTION m_eReductionStrategy = eDEFAULT_REDUCTION;
            std::unique_ptr<IReductionStrategy> m_pReductionStrategy;
            double m_dKnownOptimum;
    };


}


#endif //SEMINAR_TASK_5_SALESMANTASK_H
