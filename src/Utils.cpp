//
// Created by wjg on 18-3-28.
//

#include <Utils.h>
#include <numeric>
#include <algorithm>
#include <json/json.h>
#include <Point.h>
#include <Map.h>
#include <iomanip>
#include <fstream>

void Utils::normalize(vector<double>& v)
{
    double sum = accumulate(v.cbegin(), v.cend(), 0.0);
    if (sum > 0.0)
    {
        std::transform(v.cbegin(), v.cend(), v.begin(), [sum](double a) { return a/sum; });
    }
}

double Utils::getRandom()
{
    return dis(gen);
}

void Utils::initRandomGenerator()
{
    random_device rd;
    gen = std::mt19937(rd());
}

void Utils::toJsonFile(string filename, const int height, const int width, const vector<Point>& path, const Point& startPoint, const Point& destinationPoint, const vector<Point>& obstacles)
{
    Json::Value root;
    root["height"] = height;
    root["width"] = width;
    Json::Value arrayObj;
    Json::Value item;
    item[0] = startPoint.x;
    item[1] = startPoint.y;
    item[2] = 1;
    arrayObj.append(item);
    for (int i = 0; i < path.size(); i++)
    {
        Json::Value item;
        item[0] = path[i].x;
        item[1] = path[i].y;
        item[2] = 3;
        arrayObj.append(item);
    }
    item[0] = destinationPoint.x;
    item[1] = destinationPoint.y;
    item[2] = 2;
    arrayObj.append(item);
    for (int i = 0; i < obstacles.size(); i++)
    {
        Json::Value item;
        item[0] = obstacles[i].x;
        item[1] = obstacles[i].y;
        item[2] = 0;
        arrayObj.append(item);
    }
    root["data"] = arrayObj;

    ofstream out(filename);
    out << root.toStyledString() << endl;
    out.close();
}

vector<vector<double>> Utils::printPheromones(const Map& map, string name)
{
    vector<vector<double>> pheromones(map.height, vector<double>(map.width, 0.0));
    for (int i=0; i<map.height; i++)
    {
        for (int j=0; j<map.width; j++)
        {
            for (int k=0; k<3; k++)
            {
                for (int l=0; l<3; l++)
                {
                    if (i + k - 1 >= 0 && i + k - 1 < map.height && j + l - 1 >= 0 && j + l - 1 < map.width)
                    {
                        pheromones[i + k - 1][j + l - 1] += map.map[i][j].pheromone[k][l];
                    }
                }
            }
        }
    }
    cout << name << endl;
    for (int i=0; i<map.height; i++)
    {
        for (int j=0; j<map.width; j++)
        {
            cout << fixed << setprecision(3) << pheromones[i][j] << " ";
        }
        cout << endl;
    }
    return pheromones;
}

mt19937 Utils::gen;
uniform_real_distribution<> Utils::dis = uniform_real_distribution<double>(0, 1);

void Utils::addObstacle(vector<Point>& obstacles, Point point1, Point point2) {

    int x1 = point1.x;
    int y1 = point1.y;
    int x2 = point2.x;
    int y2 = point2.y;
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    if (deltaX == 0 && deltaY == 0)
    {
        return;
    }
    if (abs(deltaX) >= abs(deltaY))
    {
        double slope = (y2 - y1) / (x2 - x1);

        for (int i=x1; i!=x2; x1>x2?i--:i++)
        {
            obstacles.emplace_back(x1 + i, (int)(y1 + i * slope));
        }
    } else
    {
        double slope = (x2 - x1) / (y2 - y1);
        for (int i=y1; i!=y2; y1>y2?i--:i++)
        {
            obstacles.emplace_back((int)(x1 + (i - y1) * slope), i);
        }
    }


}
