//
// Created by wjg on 18-3-28.
//


#include <AntAlgorithm.h>
#include <Map.h>
#include <vector>
#include <Utils.h>

using namespace std;

AntAlgorithm::AntAlgorithm(Map map): map(map) {}

void AntAlgorithm::releaseAnts(int antNum)
{
    for (int i=0; i<antNum; i++)
    {
        Ant ant(map.startPoint);
        ant.search(map);
        ants.push_back(ant);
    }
}

void AntAlgorithm::update()
{
//        Map newMap(map.height, map.width);
    Map newMap(map.height, map.width, Point(0, 0), Point(0, 0), vector<Point>());
    int availableAntNum = 0;
    for (int i=0; i<ants.size(); i++)
    {
        if (!ants[i].path.back().isSamePoint(map.destinationPoint))
        {
            continue;
        }
        cout << "An ant reach destination." << endl;
        availableAntNum++;
        Ant& ant = ants[i];
        // Always save shortest path.
        if (shortestPath.empty() || ant.path.size() < shortestPath.size())
        {
            shortestPath = ant.path;
        }
        double stepPheromones = map.fullPheromones / ant.path.size();
//            cout << "stepPheromones = " << stepPheromones << endl;


        for (int j=0; j<ant.path.size()-1; j++)
        {
            newMap.map[ant.path[j].y][ant.path[j].x].pheromone[ant.path[j+1].y - ant.path[j].y + 1][ant.path[j+1].x - ant.path[j].x + 1] += stepPheromones;
        }

//        Utils::printPheromones(newMap, "ant " + i);
    }

    // Need normalization ?

    map.merge(newMap, 0.2);

//    Utils::printPheromones(map, "map");

}

vector<Point> AntAlgorithm::evaluate()
{
    return shortestPath;
}