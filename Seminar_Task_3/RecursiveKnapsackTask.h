//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_RECURSIVEKNAPSACKTASK_H
#define SEMINAR_TASK_3_RECURSIVEKNAPSACKTASK_H

#include <map>
#include "BaseKnapsackTask.h"

struct kwPair
{
    kwPair(int k, int w)
    : m_k(k),
      m_w(w)
    {}

    bool operator<(const kwPair& rhs) const
    {
        return (std::tie(m_k, m_w) < std::tie(rhs.m_k, rhs.m_w));
    }

    bool operator==(const kwPair& rhs) const
    {
        return ((m_k == rhs.m_k) && (m_w == rhs.m_w));
    }
    int m_k;
    int m_w;
};

struct zxPair
{
    explicit zxPair(int z = 0, std::vector<bool> x = {})
    : m_z(z),
      m_x(x)
    {}



    int m_z;
    std::vector<bool> m_x;
};

class RecursiveKnapsackTask : public BaseKnapsackTask
{
    public:
        explicit RecursiveKnapsackTask(const std::string& sTaskPath)
                 : BaseKnapsackTask(sTaskPath)
        {}
        void doSolve(int k) override;

    private:
        int SolveSubTask(int k, int w);
        std::map<kwPair, zxPair> m_Cache;
};


#endif //SEMINAR_TASK_3_RECURSIVEKNAPSACKTASK_H
