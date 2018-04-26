//
// Created by wjg on 18-3-28.
//

#ifndef ANTPATHPLANNING_POINT_H
#define ANTPATHPLANNING_POINT_H

#include <iostream>

using namespace std;

/**
 * Point entity with relevant pheromones.
 */
class Point {

public:
    Point(int x, int y);

    double distance(const Point& point);

    bool isSamePoint(const Point& point);

    int x;
    int y;
    double pheromone[3][3];

};

ostream& operator<<(ostream& os, const Point& point);


#endif //ANTPATHPLANNING_POINT_H
