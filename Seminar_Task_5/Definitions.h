//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_DEFINITIONS_H
#define SEMINAR_TASK_5_DEFINITIONS_H

#include <memory>
const int DEFAULT_ALPHA = 10;
const int DEFAULT_BETA = 3;
const int MAX_TASK_SIZE_FOR_GREEDY_SOLVE = 3;

const int INCORRECT_VALUE = -1;


enum etREDUCTION
{
    eUNDEFINED_REDUCTION = -1,
    eDEFAULT_REDUCTION = 0,
    eCENTER_RECALC_REDUCTION
};


namespace TSP
{
    class SalesmanTask;
    struct CPoint;
    struct Cluster;
    struct CenteredCluster;
    using SubTaskList = std::shared_ptr<std::vector<SalesmanTask>>;
    using ClusterList = std::vector<std::shared_ptr<Cluster>>;
    using CenteredClusterList = std::vector<CenteredCluster>;
    using PointList = std::vector<CPoint>;
    using Permutation = std::vector<int>;
}

#endif //SEMINAR_TASK_5_DEFINITIONS_H
