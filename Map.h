#ifndef Map_H
#define Map_H
#include <bits/stdc++.h>
class Car;
class Station;
using namespace std;

class Map 
{
public:
    Map(double w, double l);
    void addCar(Car);
    void addStation(Station);
    void check();
    void render();
    void run();
    pair<double,double> getSize();

private:
    double width, length;
    vector<Car> cars;
    vector<Station> stations;
    vector<int> changeTime;
};
#endif