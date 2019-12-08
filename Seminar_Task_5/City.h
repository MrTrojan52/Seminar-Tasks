//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_CITY_H
#define SEMINAR_TASK_5_CITY_H

#include "Point.h"

namespace TSP
{
    struct CCity
    {
        CCity(int nNum, CPoint loc)
                : m_nNumber(nNum),
                  m_Location(loc)
        { }

        int m_nNumber;
        CPoint m_Location;

        [[nodiscard]] double DistanceTo(const CCity& rhs) const
        {
            return m_Location.DistanceTo(rhs.m_Location);
        }
    };
}

#endif //SEMINAR_TASK_5_CITY_H
