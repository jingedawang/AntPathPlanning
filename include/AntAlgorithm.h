//
// Created by wjg on 18-3-28.
//

#ifndef ANTPATHPLANNING_ANTALGORITHM_H
#define ANTPATHPLANNING_ANTALGORITHM_H


#include "Ant.h"

/**
 * Ant colony algorithm used for path planning in grid map.
 */
class AntAlgorithm {

public:
    AntAlgorithm(Map map);

    void releaseAnts(int antNum);

    void update();

    vector<Point> evaluate();

private:
    Map map;
    vector<Ant> ants;
    vector<Point> shortestPath;

};


#endif //ANTPATHPLANNING_ANTALGORITHM_H
