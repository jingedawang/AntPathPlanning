#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <Utils.h>
#include <AntAlgorithm.h>
#include <chrono>

using namespace std;

int main() {

    Utils::initRandomGenerator();

    // Construct map.
    const int iterateNum = 30;
    const int antNum = 50;
    const int height = 30;
    const int width = 30;
    const Point startPoint(1, 1);
    const Point destinationPoint(width - 2, height - 2);
    vector<Point> obstacles;
    for (int i=0; i<height/3*2; i++)
    {
        obstacles.emplace_back(width/3, i);
    }
    for (int i=height/3; i<height; i++)
    {
        obstacles.emplace_back(width/3*2, i);
    }
    Map map(height, width, startPoint, destinationPoint, obstacles);

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    // Path planning using ant algorithm.
    AntAlgorithm algorithm(map);
    for (int i=0; i<iterateNum; i++)
    {
        algorithm.releaseAnts(antNum);
        algorithm.update();
    }
    vector<Point> shortestPath = algorithm.evaluate();

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

    // Print shortest path.
    for (int i=0; i<shortestPath.size(); i++)
    {
        cout << shortestPath[i] << endl;
    }

    // Write results to text file.
    Utils::toJsonFile("out.txt", height, width, shortestPath, startPoint, destinationPoint, obstacles);

    double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();
    cout << "Time used: " << ttrack << endl;
    cout << "Path length: " << shortestPath.size() << endl;

    return 0;
}