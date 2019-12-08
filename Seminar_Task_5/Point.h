//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_POINT_H
#define SEMINAR_TASK_5_POINT_H

#include <istream>
#include <cmath>

namespace TSP
{
    struct CPoint
    {
        explicit CPoint(double X = 0, double Y = 0)
                : m_X(X),
                  m_Y(Y)
        { }

        friend std::istream& operator>>(std::istream& is, CPoint& pt)
        {
            is >> pt.m_X >> pt.m_Y;
            return is;
        }

        [[nodiscard]] double DistanceTo(const CPoint& rhs) const
        {
            double dX = m_X - rhs.m_X;
            double dY = m_Y - rhs.m_Y;
            return sqrt((dX * dX) + (dY * dY));
        }

        double m_X;
        double m_Y;
    };
}

#endif //SEMINAR_TASK_5_POINT_H
