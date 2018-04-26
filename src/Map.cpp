//
// Created by wjg on 18-3-28.
//

#include <vector>

#include "Map.h"

using namespace std;

Map::Map(int height, int width, Point startPoint, Point destinationPoint, vector <Point> obstacles)
        : height(height), width(width), startPoint(startPoint), destinationPoint(destinationPoint) {
    // Initialize map
    for (int i=0; i<height; i++)
    {
        vector<Point> row;
        for (int j=0; j<width; j++)
        {
            row.emplace_back(j, i);
        }
        map.push_back(row);
    }

    // Initialize obstacle map
    for (int i=0; i<height; i++)
    {
        obstacleMap.emplace_back(width, false);
    }
    for (int i=0; i<obstacles.size(); i++)
    {
        obstacleMap[obstacles[i].y][obstacles[i].x] = true;
    }
}

Point Map::getPoint(int x, int y) const
{
    return Point(map[y][x]);
}

bool Map::isObstacle(int x, int y) const
{
    return obstacleMap[y][x];
}