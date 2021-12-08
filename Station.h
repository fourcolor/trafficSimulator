#pragma once
#include <bits/stdc++.h>

class Station
{
public:
    Station(double x, double y, int id);
private:
    double x, y;
    double freq;
    int id;
};