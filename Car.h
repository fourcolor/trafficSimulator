#ifndef Car_H
#define Car_H
#include <bits/stdc++.h>
class Map;

using namespace std;

class Car
{
public:
    Car(double x, double y, double s, double pMin, double E, int dir);
    void move();
    void chooseStation(Map);
    pair<int,int> getPos();

private:
    void turn(int flag);
    double x, y;
    double speed;
    vector<double> CDF = {0.5, 0.71875, 0.8373, 1.0};
    double pMin = 100;
    double E = 25;
    double direction;
    int stationId = -1;
};
#endif