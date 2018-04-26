//
// Created by wjg on 18-3-28.
//

#ifndef ANTPATHPLANNING_ANT_H
#define ANTPATHPLANNING_ANT_H

#include <vector>
#include <Point.h>
#include <Map.h>

using namespace std;

/**
 * Individual ant used to randomly search.
 */
class Ant {

public:
    Ant(Point startPosition);

    void search(const Map& map);

    vector<Point> path;

private:
    Point currentPosition;

};


#endif //ANTPATHPLANNING_ANT_H
