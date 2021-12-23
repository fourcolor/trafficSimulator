#ifndef Car_H
#define Car_H
#include <bits/stdc++.h>
class Station;
class Map;
using namespace std;
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};
class Car
{
public:
    Car(double x, double y, double s, double pMin, double E, Direction dir);
    vector<int> moveAndConnect(Map,vector<Station> stations);
    vector<int> chooseStation(vector<Station>);
    pair<double, int> getIntensity(Station);
    pair<double, double> getPos();
    void recordIntensity(vector<Station>);
    void oneHourSet();

private:
    void turn(int flag);
    double x, y;
    vector<double> record;
    vector<double> predict;
    double speed;
    double CDF[4] = {1.0 / 2, 1.0 / 2 + 7.0 / 32, 1.0 / 2 + 7.0 / 32 + 1.0 / 16, 1.0};
    double pMin = 23;
    double E = 5;
    Direction direction;
    int stationId[4] = {-1};
    int time;
    vector<pair<int,int>> connectTime;
};
#endif