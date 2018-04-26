//
// Created by wjg on 18-3-28.
//

#include <cmath>
#include "Point.h"

Point::Point(int x, int y) : x(x), y(y)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            pheromone[i][j] = 0.0;
        }
    }
}

double Point::distance(const Point& point)
{
    return sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
}

bool Point::isSamePoint(const Point& point)
{
    return x == point.x && y == point.y;
}

ostream& operator<<(ostream& os, const Point& point)
{
    os << "[" << point.x << " ," << point.y << "] [";
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            os << point.pheromone[i][j] << " ";
        }
    }
    os << "]";
    return os;
}