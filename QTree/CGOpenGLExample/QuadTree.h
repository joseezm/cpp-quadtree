#pragma once

#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>

#define KEY_ESC 27

using namespace std;

struct Point
{
	float x;
	float y;
	Point(float _x, float _y);
	Point();
	void print();
};


class Quad
{
public:

	Point topLeft;
	Point botRight;
	vector <Point*> Puntos;
	Quad* topLeftTree;
	Quad* topRightTree;
	Quad* botLeftTree;
	Quad* botRightTree;

	int n;

	bool cuadro = false;
	int xCuadro, yCuadro;
	vector <Point*> points;

	Quad(Point topL, Point botR, int n_);

	void insert(float x, float y);

	bool inBoundary(float x, float y);
	bool intersection(Point c1, Point c2, Quad * tree);

	void draw();
	void drawPoint(int xP,int yP);
	void drawCuadro(int n);

	void Find(Point x, Point y);

};

