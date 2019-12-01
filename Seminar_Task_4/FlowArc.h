//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_FLOWARC_H
#define SEMINAR_TASK_4_FLOWARC_H


struct CFlowArc
{
    int m_nFrom;
    int m_nTo;
    int m_nWeight;

    CFlowArc(int nFrom, int nTo, int nWeight)
    : m_nFrom(nFrom),
      m_nTo(nTo),
      m_nWeight(nWeight)
    { }
};


#endif //SEMINAR_TASK_4_FLOWARC_H
