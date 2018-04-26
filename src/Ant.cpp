//
// Created by wjg on 18-3-28.
//

#include <vector>
#include <Point.h>
#include <Map.h>
#include <Utils.h>
#include <algorithm>
#include "Ant.h"

using namespace std;

Ant::Ant(Point startPosition) : currentPosition(startPosition) {}

void Ant::search(const Map& map)
{
    int stepCount = 0;
    while (stepCount < map.height * map.width && !currentPosition.isSamePoint(map.destinationPoint))
    {
        vector<double> pheromones;
        vector<double> distancesToDestinationReciprocal;
        vector<double> angleWeights;
        vector<Point> neighborIndices;

        Point currentPositionInMap = map.getPoint(currentPosition.x, currentPosition.y);
        int deltaX = map.destinationPoint.x - currentPositionInMap.x;
        int deltaY = map.destinationPoint.y - currentPositionInMap.y;
        double theta = atan2(deltaY, deltaX);
        vector<vector<double>> angle = {{-3*M_PI/4, -M_PI, 3*M_PI/4}, {-M_PI/2, 0, M_PI/2}, {-M_PI/4, 0, M_PI/4}};
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
            {
                int nextX = currentPositionInMap.x + i - 1;
                int nextY = currentPositionInMap.y + j - 1;
                if ((i == 1 && j == 1) || nextX < 0 || nextX >= map.width || nextY < 0 || nextY >= map.height || map.isObstacle(nextX, nextY))
                {
                    continue;
                }
                pheromones.push_back(currentPositionInMap.pheromone[i][j]);
                distancesToDestinationReciprocal.push_back(1.0 / (Point(nextX, nextY).distance(map.destinationPoint) + 0.001));
                neighborIndices.push_back(Point(nextX, nextY));

                // Compute angle direction score
                angle[i][j] -= theta;
                if (angle[i][j] < -M_PI)
                {
                    angle[i][j] += 2 * M_PI;
                }
                else if (angle[i][j] > M_PI)
                {
                    angle[i][j] -= 2 * M_PI;
                }
                angleWeights.push_back(pow(1.2, -4*abs(angle[i][j])/M_PI));
            }
        }

        if (pheromones.empty())
        {
            break;
        }

        Utils::normalize(pheromones);
        Utils::normalize(distancesToDestinationReciprocal);
        Utils::normalize(angleWeights);
        vector<double> weightedFactor(pheromones.size());
//        std::transform(pheromones.cbegin(), pheromones.cend(), distancesToDestinationReciprocal.cbegin(), weightedFactor.begin(), [](double a, double b) {return a + 5*b;});
        std::transform(pheromones.cbegin(), pheromones.cend(), angleWeights.cbegin(), weightedFactor.begin(), [](double a, double b) {return a + b;});
        Utils::normalize(weightedFactor);

        Point selectedPosition(0.0, 0.0);

        double sumPrevious = 0.0;
        double randomNumber = Utils::getRandom();
        for (int i=0; i<weightedFactor.size(); i++)
        {
            if (randomNumber >= sumPrevious && randomNumber < sumPrevious + weightedFactor[i])
            {
                selectedPosition = neighborIndices[i];
                break;
            }
            sumPrevious += weightedFactor[i];
        }
        currentPosition = selectedPosition;
        path.push_back(selectedPosition);
        stepCount++;
    }
}