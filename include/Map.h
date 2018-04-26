//
// Created by wjg on 18-3-28.
//

#ifndef ANTPATHPLANNING_MAP_H
#define ANTPATHPLANNING_MAP_H

#include "Point.h"

/**
 * Grid map which contains obstacles.
 */
class Map {

public:
    Map(int height, int width, Point startPoint, Point destinationPoint, vector<Point> obstacles);

    Map(int height, int width) : Map(height, width, Point(0, 0), Point(0, 0), vector<Point>()) {}

    const int height;
    const int width;
    const Point startPoint;
    const Point destinationPoint;

    Point getPoint(int x, int y) const;

    bool isObstacle(int x, int y) const;

    void merge(Map& newMap, double volatilizationRatio)
    {
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                for (int k=0; k<3; k++)
                {
                    for (int l=0; l<3; l++)
                    {
                        map[i][j].pheromone[k][l] = map[i][j].pheromone[k][l] * (1 - volatilizationRatio) + newMap.map[i][j].pheromone[k][l] * volatilizationRatio;
                    }
                }
            }
        }
    }

    const double fullPheromones = 1.0;
    vector<vector<Point>> map;

private:

    vector<vector<bool>> obstacleMap;

};


#endif //ANTPATHPLANNING_MAP_H
