#pragma once
#include <bits/stdc++.h>
#include "Station.h"
using namespace std;
std::default_random_engine generatorS;
std::uniform_real_distribution<float> unifS(0.0, 1.0);
Station::Station(double x, double y, int id)
{
    float prob = unifS(generatorS);
    this->x = x;
    this->y = y;
    this->id = id;
    for (int i = 1; i <= 10; i++)
    {
        if (prob < 0.1 * i)
        {
            this->freq = 100 * i;
            cout << this->freq << endl;
            break;
        }
    }
}

pair<double, double> Station::getPos()
{
    return {this->x, this->y};
}

int Station::getId()
{
    return this->id;
}

double Station::getFreq()
{
    return this->freq;
}