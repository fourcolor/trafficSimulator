#pragma once
#include <bits/stdc++.h>
#include "Car.h"
#include "Map.h"
#include "Station.h"
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<float> unif(0.0, 1.0);
std::uniform_real_distribution<float> unif2(0.0, 100.0);
double a = 0.5;
Car::Car(double x, double y, double s, double pMin, double E, Direction dir)
{
    this->x = x;
    this->y = y;
    this->speed = s;
    this->pMin = pMin;
    this->E = E;
    this->direction = dir;
    this->time = 0;
    this->stationId[0] = -1;
    this->stationId[1] = -1;
    this->stationId[2] = -1;
    this->stationId[3] = -1;
    oneHourSet();
}
bool timeCheck(vector<pair<int, int>> tmp, int start, int end)
{
    for (auto i : tmp)
    {
        if ((start > i.first && start < i.second) || (end > i.first && end < i.second))
        {
            return false;
        }
    }
    return true;
}
vector<int> Car::moveAndConnect(Map m, vector<Station> stations)
{
    // cout << this->direction;
    int dir = this->direction;
    set<double> sx;
    set<double> sy;
    float x_pos = 0;
    float y_pos = 0;
    for (int i = 0; i < 25; i++)
    {
        sx.insert(x_pos);
        sy.insert(y_pos);
        x_pos += m.getSize().first / 10;
        y_pos += m.getSize().second / 10;
    }
    // cout << (int)(sx.find(this->x) != sx.end() && sy.find(this->y) != sy.end()) << endl;
    if (sx.find(this->x) != sx.end() && sy.find(this->y) != sy.end())
    {
        double flag = unif(generator);
        for (int i = 0; i < 4; i++)
        {
            // cout << " " << flag << " " << this->CDF[i] << " " << i << " " << endl;
            if (flag < (this->CDF[i]))
            {
                dir += i;
                dir %= 4;
                this->direction = (Direction)dir;
                break;
            }
        }
    }
    // cout << " " << this->direction << endl;
    dir = this->direction;
    switch (dir)
    {
    case UP:
        this->y += this->speed;
        break;
    case RIGHT:
        this->x += this->speed;
        break;
    case DOWN:
        this->y -= this->speed;
        break;
    case LEFT:
        this->x -= this->speed;
        break;
    }
    vector<int> changeAmount(4);
    for (auto i : this->connectTime)
    {
        if (time >= i.first && time <= i.second)
        {
            changeAmount = chooseStation(stations);
        }
    }
    time++;
    time %= 3600;
    return changeAmount;
}

pair<double, double> Car::getPos()
{
    return {this->x, this->y};
}

bool intensityCmp(pair<double, int> a, pair<double, int> b)
{
    return a.first > b.first;
}

vector<int> Car::chooseStation(vector<Station> stations)
{
    vector<pair<double, int>> intensities;
    vector<int> changeAmount(4);
    bool flag[4] = {false};
    double al1Intensity = 0, al2Intensity = 0, al3Intensity = 0, al4Intensity = 0;
    int index = 0;
    double maxAl4Val = 0;
    int maxAl4Id = 0;
    for (auto i = stations.begin(); i < stations.end(); i++)
    {
        pair<double, int> intensity = this->getIntensity((*i));
        intensities.push_back(intensity);
        if (this->record.size() != stations.size())
        {
            this->record.push_back(intensity.first * a);
        }
        else
        {
            this->record[index] = intensity.first * a + (1 - a) * this->record[index];
        }
        if (maxAl4Val < this->record[index])
        {
            maxAl4Val = this->record[index];
            maxAl4Id = index;
        }
        if ((*i).getId() == this->stationId[0])
        {
            al1Intensity = intensities.rbegin()->first;
            // cout << (*i).getId() << " " << intensities.rbegin()->first << endl;
        }
        if ((*i).getId() == this->stationId[1])
        {
            al2Intensity = intensities.rbegin()->first;
            // cout << (*i).getId() << " " << intensities.rbegin()->first << endl;
        }
        if ((*i).getId() == this->stationId[2])
        {
            al3Intensity = intensities.rbegin()->first;
            // cout << (*i).getId() << " " << intensities.rbegin()->first << endl;
        }
        if ((*i).getId() == this->stationId[3])
        {
            al4Intensity = intensities.rbegin()->first;
            // cout << (*i).getId() << " " << intensities.rbegin()->first << endl;
        }
        index++;
    }
    for (int j = 0; j < 4; j++)
    {
        if (this->stationId[j] == -1)
        {
            flag[j] = true;
        }
    }
    sort(intensities.begin(), intensities.end(), intensityCmp);
    // cout << intensities[0].first << " " << al1Intensity << " " << al2Intensity << " " << al3Intensity << " " << al4Intensity << endl;
    if (intensities[0].first < this->pMin)
    {
        cout << "error" << endl;
    }
    // cout << (this->stationId[0] == -1 || al1Intensity < this->pMin) << " " << (this->stationId[1] == -1 || al2Intensity != intensities[0].first) << " " << ((this->stationId[2] == -1) || (intensities[0].first - al3Intensity > this->E) || al3Intensity < this->pMin) << " " << ((this->stationId[3] == -1) || al4Intensity < this->pMin) << endl;
    //    algo 1
    if (this->stationId[0] == -1 || al1Intensity < this->pMin)
    {
        if (this->stationId[0] != intensities[0].second)
        {
            this->stationId[0] = intensities[0].second;
            if (this->stationId[0] != -1)
            {
                changeAmount[0]++;
            }
        }
    }

    // algo 2
    if (this->stationId[1] == -1 || al2Intensity != intensities[0].first)
    {
        if (this->stationId[1] != intensities[0].second)
        {
            this->stationId[1] = intensities[0].second;
            if (this->stationId[1] != -1)
            {
                changeAmount[1]++;
            }
        }
    }

    // algo 3
    if ((this->stationId[2] == -1) || (intensities[0].first - al3Intensity > this->E) || al3Intensity < this->pMin)
    {
        // cout << (this->stationId[2] != intensities[0].second) << " " << this->stationId[2] << endl;
        if (this->stationId[2] != intensities[0].second)
        {
            this->stationId[2] = intensities[0].second;
            if (this->stationId[2] != -1)
            {
                changeAmount[2]++;
            }
        }
    }

    // algo 4

    if ((this->stationId[3] == -1) || al4Intensity < this->pMin)
    {
        if (this->stationId[3] != maxAl4Id)
        {
            this->stationId[3] = maxAl4Id;
            if (this->stationId[3] != -1)
            {
                changeAmount[3]++;
            }
        }
    }
    else
    {
        double k = unif2(generator);
        if (k > 99.9)
        {
            if (this->stationId[3] != maxAl4Id)
            {
                this->stationId[3] = maxAl4Id;
                if (this->stationId[3] != -1)
                {
                    changeAmount[3]++;
                }
            }
        }
    }
    // cout << changeAmount[0] << " " << changeAmount[1] << " " << changeAmount[2] << " " << changeAmount[3] << endl;
    return changeAmount;
}

void Car::recordIntensity(vector<Station> stations)
{
    vector<pair<double, int>> intensities;
    int index = 0;
    for (auto i = stations.begin(); i < stations.end(); i++)
    {
        pair<double, int> intensity = this->getIntensity((*i));
        intensities.push_back(intensity);
        if (this->record.size() != stations.size())
        {
            this->record.push_back(intensity.first * a);
        }
        else
        {
            this->record[index] = intensity.first * a + (1 - a) * this->record[index];
            index++;
        }
    }
}

double calDistance(double x1, double y1, double x2, double y2)
{
    double res = abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2);
    res = sqrt(res) / 1000;
    return res;
}

pair<double, int> Car::getIntensity(Station s)
{
    pair<double, int> res;
    // cout << s.getFreq() << endl;
    res.first = 120 - (32.45 + 20 * log10(s.getFreq()) + 20 * log10(calDistance(s.getPos().first, s.getPos().second, this->x, this->y)));
    res.second = s.getId();
    return res;
}
normal_distribution<double> distribution(2, 1);
normal_distribution<double> distribution2(300, 30);
uniform_real_distribution<float> unifC(3600, 0);
void Car::oneHourSet()
{
    int number = distribution(generator);
    if (number < 0)
    {
        number = distribution(generator);
    }
    vector<pair<int, int>> tmp;
    for (int i = 0; i < number; i++)
    {
        int start, dur;
        dur = distribution2(generator);
        do
        {
            start = unifC(generator);
        } while (!timeCheck(tmp, start, start + dur));
        tmp.push_back({start, start + dur});
    }
    this->connectTime = tmp;
}