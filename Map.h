#ifndef Map_H
#define Map_H
#include <bits/stdc++.h>
#include "Station.h"
#include "Car.h"
class Map
{
public:
    Map(double w, double l);
    void addCar(Car);
    void addStation(Station);
    void check();
    void render();

private:
    double width, length;
    multiset<Car> cars;
    multiset<Station> stations;
};
#endif