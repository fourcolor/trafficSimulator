#pragma once
#include <bits/stdc++.h>
using namespace std;
class Station
{
public:
    Station(double x, double y, int id);
    pair<double, double> getPos();
    int getId();
    double getFreq();
private:
    double x, y;
    double freq;
    int id;
};