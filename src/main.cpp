#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <Utils.h>
#include <AntAlgorithm.h>

using namespace std;

int main() {

    Utils::initRandomGenerator();

    // Construct map.
    const int iterateNum = 50;
    const int antNum = 50;
    const int height = 50;
    const int width = 50;
    const Point startPoint(1, 1);
    const Point destinationPoint(48, 48);
//    vector<Point> obstacles = { {10, 8}, {10, 9}, {10, 10}, {10, 11}, {10, 12}};
    vector<Point> obstacles;
    for (int i=0; i<30; i++)
    {
        obstacles.emplace_back(10, i);
    }
    for (int i=20; i<50; i++)
    {
        obstacles.emplace_back(40, i);
    }
    Map map(height, width, startPoint, destinationPoint, obstacles);

    // Path planning using ant algorithm.
    AntAlgorithm algorithm(map);
    for (int i=0; i<iterateNum; i++)
    {
        algorithm.releaseAnts(antNum);
        algorithm.update();
    }
    vector<Point> shortestPath = algorithm.evaluate();

    // Print shortest path.
    for (int i=0; i<shortestPath.size(); i++)
    {
        cout << shortestPath[i] << endl;
    }

    // Write results to text file.
    Utils::toJsonFile("out.txt", height, width, shortestPath, startPoint, destinationPoint, obstacles);

    return 0;
}