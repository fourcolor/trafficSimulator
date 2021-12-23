#pragma once
#include "Map.h"
#include "Station.h"
#include "Car.h"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

Map::Map(double w, double l)
{
    this->width = w;
    this->length = l;
    this->changeTime.push_back(0);
    this->changeTime.push_back(0);
    this->changeTime.push_back(0);
    this->changeTime.push_back(0);
}

void Map::addCar(Car car)
{
    this->cars.push_back(car);
}

void Map::addStation(Station s)
{
    this->stations.push_back(s);
}

void Map::check()
{
    for (auto i = this->cars.begin(); i < this->cars.end(); i++)
    {
        pair<int, int> cpos = i->getPos();
        if (cpos.first > this->width || cpos.first < 0)
        {
            this->cars.erase(i);
        }
        if (cpos.second > this->length || cpos.second < 0)
        {
            this->cars.erase(i);
        }
    }
}

void output(int x, int y, string s)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    int len, i;
    len = s.size();
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
    }
}

void Map::render()
{
    string s[5];
    s[0] = "Algorithm 1 Minium: ";
    s[1] = "Algorithm 2 Best Effort: ";
    s[2] = "Algorithm 3 Entropy: ";
    s[3] = "Algorithm 4 Predict: ";
    s[4] = "Total car: ";
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glLineWidth(3);
    glPointSize(7);
    // Background
    glBegin(GL_LINES);
    glColor3f(0.5, 0.5, 0.5);
    float x_pos = this->width / 50;
    for (int i = 0; i < 25; i++)
    {
        glVertex2f(x_pos, this->length / 50);
        glVertex2f(x_pos, this->length + this->length / 50);
        glVertex2f(this->width / 50, x_pos);
        glVertex2f(this->width + this->width / 50, x_pos);
        x_pos += this->width / 10;
    }
    glEnd();
    // Car
    glBegin(GL_POINTS);
    glColor3f(0.3, 1, 0.8);
    for (auto i : this->cars)
    {
        glVertex2f(i.getPos().first + this->width / 50, i.getPos().second + this->length / 50);
    }
    glEnd();
    // Station
    glBegin(GL_POINTS);
    glColor3f(0.9, 0.5, 0.4);
    for (auto i : this->stations)
    {
        glVertex2f(i.getPos().first + this->width / 50, i.getPos().second + this->length / 50);
    }
    glEnd();
    s[0] = s[0] + to_string(this->changeTime[0]);
    s[1] = s[1] + to_string(this->changeTime[1]);
    s[2] = s[2] + to_string(this->changeTime[2]);
    s[3] = s[3] + to_string(this->changeTime[3]);
    s[4] = s[4] + to_string(this->cars.size());
    output((this->width + this->width / 25) / 4, -(this->length + this->length / 25) / 2 / 6 * 1, s[0]);
    output((this->width + this->width / 25) / 4, -(this->length + this->length / 25) / 2 / 6 * 2, s[1]);
    output((this->width + this->width / 25) / 4, -(this->length + this->length / 25) / 2 / 6 * 3, s[2]);
    output((this->width + this->width / 25) / 4, -(this->length + this->length / 25) / 2 / 6 * 4, s[3]);
    output((this->width + this->width / 25) / 4, -(this->length + this->length / 25) / 2 / 6 * 5, s[4]);
}

void Map::run()
{
    for (auto i = this->cars.begin(); i != this->cars.end(); i++)
    {
        vector<int> tmp;
        tmp = i->moveAndConnect(*this, this->stations);
        for (int j = 0; j < 4; j++)
        {
            this->changeTime[j] += tmp[j];
        }
    }
    this->check();
}

pair<double, double> Map::getSize()
{
    return {this->width, this->length};
}
