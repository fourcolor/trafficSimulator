#pragma once
#include "Map.h"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
Map::Map(double w, double l)
{
    this->width = w;
    this->length = l;
}

void Map::addCar(Car car)
{
    this->cars.insert(car);
}

void Map::check()
{
    for (auto i : this->cars)
    {
        pair<int, int> cpos = i.getPos();
        if (cpos.first > this->width || cpos.first < 0)
        {
            this->cars.erase(i);
            continue;
        }
        if (cpos.second > this->length || cpos.second < 0)
        {
            this->cars.erase(i);
            continue;
        }
    }
}

void Map::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.5, 0.6);
    float x_pos = 5;
    for (int i = 0; i < 25; i++)
    {
        glVertex2f(x_pos, 5);
        glVertex2f(x_pos, 255);
        x_pos += 25;
    }
    glEnd();
}