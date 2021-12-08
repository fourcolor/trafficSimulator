#pragma once
#include <bits/stdc++.h>
#include <Car.h>
enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};
Car::Car(double x, double y, double s, double pMin, double E, int dir)
{
    this->x = x;
    this->y = y;
    this->speed = s;
    this->pMin = pMin;
    this->E = E;
    this->direction = dir;
}

void Car::move()
{
    int flag = rand() % 10000;
    int dir = this->direction;
    for (int i = 0; i < 4; i++)
    {
        if (flag <= (this->CDF[i] * 10000))
        {
            dir += i;
            dir %= 4;
            this->direction = dir;
            break;
        }
    }
    switch (dir)
    {
    case UP: 
        this->y -= this->speed;
        break;
    case RIGHT: 
        this->x += this->speed;
        break;
    case DOWN:
        this->y += this->speed;
        break;
    case LEFT:
        this->x -= this->speed;
        break;
    default:
        break;
    }
}

pair<int,int> Car::getPos()
{
    return {this->x,this->y};
}