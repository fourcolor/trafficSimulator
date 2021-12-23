#pragma once
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Map.h"
#include "Station.h"
#include "Car.h"

using namespace std;
const double W = 25000;
const double L = 25000;
const double offset = 100;
const double Speed = 20;
const double Lamda = 5.0 / 60;
const double PMin = 24;
const double E = 5;
const double StationGenProb = 0.1;
const int FPS = 120;
Map *mainMap;
void setUp();
void init();
void display();
void reshape(int, int);
void timer(int);
void generateCar();

int main(int argc, char *argv[])
{
    mainMap = new Map(W, L);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 900);
    glutCreateWindow("OpenGL 2D View");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    setUp();
}

void display()
{
    mainMap->run();
    generateCar();
    mainMap->render();
    glutSwapBuffers();
}

void timer(int a)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W + W / 25, -(L + L / 25) / 2, L + L / 25);
    glMatrixMode(GL_MODELVIEW);
}
void setUp()
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> unif(0.0, 1.0);
    int id = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            float prob = unif(generator);
            if (prob < 0.1)
            {
                double x = i * W / 10 + W / 20;
                double y = j * L / 10 + L / 20;
                prob = unif(generator);
                if (prob < 0.25)
                {
                    x += offset;
                }
                else if (prob < 0.5)
                {
                    y += offset;
                }
                else if (prob < 0.75)
                {
                    x -= offset;
                }
                else
                {
                    y -= offset;
                }
                mainMap->addStation(*(new Station(x, y, id)));
                id++;
            }
        }
    }
}
void generateCar()
{
    double prob = Lamda * exp(-Lamda) / 10;
    double posx[2] = {0, W};
    double posy[2] = {0, L};
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> unif(0.0, 1.0);
    for (int i = 1; i < 10; i++)
    {
        double x = i * W / 10;
        double y = i * L / 10;
        double flag = unif(generator);
        // cout << flag << endl;

        if (flag < prob)
        {
            mainMap->addCar(*(new Car(0, y, Speed, PMin, E, RIGHT)));
        }
        flag = unif(generator);
        if (flag < prob)
        {
            mainMap->addCar(*(new Car(W, y, Speed, PMin, E, LEFT)));
        }
        flag = unif(generator);
        if (flag < prob)
        {
            mainMap->addCar(*(new Car(x, 0, Speed, PMin, E, UP)));
        }

        flag = unif(generator);
        if (flag < prob)
        {
            mainMap->addCar(*(new Car(x, L, Speed, PMin, E, DOWN)));
        }
    }
}
