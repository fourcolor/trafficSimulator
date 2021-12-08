#pragma once
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Map.h"
#include "Car.h"
#include "Station.h"

using namespace std;
const double W = 25;
const double L = 25;
const double Speed = 6.944444;
const double Lamda = 5.0 / 60 * 100;
const double StationGenProb = 0.1;
Map *mainMap;

void init();
void display();
void reshape(int, int);
void timer(int);
bool generateCar()
{
    int flag = rand() % 100;
    if (Lamda >= flag)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    mainMap = new Map(W, L);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
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
}

void display()
{

    glutSwapBuffers();
}

void timer(int a)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 260, 0, 260);
    glMatrixMode(GL_MODELVIEW);
}