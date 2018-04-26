//
// Created by wjg on 18-3-28.
//

#ifndef ANTPATHPLANNING_UTILS_H
#define ANTPATHPLANNING_UTILS_H

#include <vector>
#include <numeric>
#include <random>
#include <Point.h>
#include <Map.h>

using namespace std;

/**
 * Utility methods.
 */
class Utils {

public:

    static void normalize(vector<double>& v);

    static double getRandom();

    static void initRandomGenerator();

    static void toJsonFile(string filename,
                           const int height,
                           const int width,
                           const vector<Point>& path,
                           const Point& startPoint,
                           const Point& destinationPoint,
                           const vector<Point>& obstacles);

    static vector<vector<double>> printPheromones(const Map& map, string name);

    // Not completed.
    static void addObstacle(vector<Point>& obstacles, Point point1, Point point2);

private:
    static mt19937 gen;
    static uniform_real_distribution<> dis;


};


#endif //ANTPATHPLANNING_UTILS_H
