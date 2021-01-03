#include "QuadTree.h"
#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#define KEY_ESC 27

using namespace std;

Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}

Point::Point() {
	x = 0;
	y = 0;
}

void Point::print() {
	cout << "	" << x << "," << y << "	" << endl;
}


Quad::Quad(Point topL, Point botR, int n_) {
	n = n_;
	topLeftTree = NULL;
	topRightTree = NULL;
	botLeftTree = NULL;
	botRightTree = NULL;

	topLeft = topL;
	botRight = botR;


}

void Quad::insert(float x, float y)
{
	if (!inBoundary(x, y))
		return;

	for (int i = 0; i < Puntos.size(); i++) {
		if (Puntos[i]->x == x && Puntos[i]->y == y)
			return;
	}

	Point* nuevoPunto = new Point(x, y);

	if (Puntos.size() < n && topLeftTree == NULL) {
		Puntos.push_back(nuevoPunto);
		return;
	}

	else if (topLeftTree == NULL) {

		Point aux(topLeft.x, topLeft.y);
		Point aux2((topLeft.x+botRight.x)/2,(topLeft.y+botRight.y)/2);
		topLeftTree = new Quad(aux, aux2, n);
			
		aux.x = (topLeft.x + botRight.x) / 2;
		aux.y = topLeft.y;
		aux2.x = botRight.x;
		aux2.y = (topLeft.y + botRight.y) / 2;
		topRightTree = new Quad(aux, aux2, n);

		aux.x = topLeft.x;
		aux.y = (topLeft.y + botRight.y)/2;
		aux2.x = (topLeft.x + botRight.x) / 2;
		aux2.y = botRight.y;
		botLeftTree = new Quad(aux, aux2, n);

		aux.x = (topLeft.x + botRight.x) / 2;
		aux.y = (topLeft.y + botRight.y) / 2;
		aux2.x = botRight.x;
		aux2.y = botRight.y;
		botRightTree = new Quad(aux, aux2, n);

		for (int i = Puntos.size() - 1; i >= 0; i--) {
			if (topLeftTree->inBoundary(Puntos[i]->x, Puntos[i]->y)) {
				topLeftTree->insert(Puntos[i]->x, Puntos[i]->y);
				Puntos.pop_back();
			}
			else if (topRightTree->inBoundary(Puntos[i]->x, Puntos[i]->y)) {
				topRightTree->insert(Puntos[i]->x, Puntos[i]->y);
				Puntos.pop_back();
			}
			else if (botLeftTree->inBoundary(Puntos[i]->x, Puntos[i]->y)) {
				botLeftTree->insert(Puntos[i]->x, Puntos[i]->y);
				Puntos.pop_back();
			}
			else if (botRightTree->inBoundary(Puntos[i]->x, Puntos[i]->y)) {
				botRightTree->insert(Puntos[i]->x, Puntos[i]->y);
				Puntos.pop_back();
			}
		}
	}

	if (topLeftTree->inBoundary(nuevoPunto->x, nuevoPunto->y)) topLeftTree->insert(nuevoPunto->x, nuevoPunto->y);
	else if (topRightTree->inBoundary(nuevoPunto->x, nuevoPunto->y)) topRightTree->insert(nuevoPunto->x, nuevoPunto->y);
	else if (botLeftTree->inBoundary(nuevoPunto->x, nuevoPunto->y)) botLeftTree->insert(nuevoPunto->x, nuevoPunto->y);
	else if (botRightTree->inBoundary(nuevoPunto->x, nuevoPunto->y)) botRightTree->insert(nuevoPunto->x, nuevoPunto->y);
}

bool Quad::inBoundary(float x, float y){
	return (x >= topLeft.x && x <= botRight.x && y >= topLeft.y && y <= botRight.y);
}

bool Quad::intersection(Point c1, Point c2, Quad* tree) {

	Point a= tree->topLeft;
	Point d = tree->botRight;
	Point b(d.x, a.y);
	Point c(a.x, d.y);
	
	if (a.x >= c1.x && a.x <= c2.x && a.y >= c1.y && a.y <= c2.y) return true;
	else if (b.x >= c1.x && b.x <= c2.x && b.y >= c1.y && b.y <= c2.y) return true;
	else if (c.x >= c1.x && c.x <= c2.x && c.y >= c1.y && c.y <= c2.y) return true;
	else if (d.x >= c1.x && d.x <= c2.x && d.y >= c1.y && d.y <= c2.y) return true;
	else return false;


}

void Quad::draw() {

	glLineWidth(2);
	if (topLeftTree) {
		topLeftTree->draw();
		topRightTree->draw();
		botLeftTree->draw();
		botRightTree->draw();
	}

	for (int i = 0; i < Puntos.size(); i++) {
		drawPoint(Puntos[i]->x, Puntos[i]->y);
	}

	if (cuadro) {
		drawCuadro(80);
		Find(Point(xCuadro - 80, yCuadro - 80), Point(xCuadro, yCuadro));
	}

	// if (this->Puntos.empty()) return;

	glBegin(GL_LINES);
	glColor3d(0.13f, 0.52f, 0.75f);
	glVertex2d(topLeft.x, topLeft.y);
	glVertex2d(topLeft.x, botRight.y);
	glVertex2d(topLeft.x, botRight.y);
	glVertex2d(botRight.x, botRight.y);
	glVertex2d(botRight.x, botRight.y);
	glVertex2d(botRight.x, topLeft.y);
	glVertex2d(botRight.x, topLeft.y);
	glVertex2d(topLeft.x, topLeft.y);
	glEnd();


}
void Quad::drawPoint(int xP, int yP) {

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3d(1.0f, 1.0f, 1.0f);
	glVertex2d(xP, yP);
	glEnd();
}

void Quad::drawCuadro(int n) {
		glBegin(GL_LINES);
		glColor3d(1.0f, 0.0f, 0.0f);
		glVertex2d(xCuadro, yCuadro);
		glVertex2d((xCuadro - n), (yCuadro));
		glVertex2d((xCuadro - n), (yCuadro));
		glVertex2d((xCuadro - n), (yCuadro - n));
		glVertex2d((xCuadro - n), (yCuadro - n));
		glVertex2d((xCuadro), (yCuadro - n));
		glVertex2d((xCuadro), (yCuadro - n));
		glVertex2d((xCuadro), (yCuadro));
		glEnd();
}

void Quad::Find(Point x, Point y) {
	

	Point a = x;
	Point d = y;
	Point b;
	b.x = d.x;
	b.y = a.y;
	Point c;
	c.x = a.x;
	c.y = d.y;


	if (topLeftTree) {
		if (topLeftTree->inBoundary(a.x, a.y) || topLeftTree->inBoundary(b.x, b.y) || topLeftTree->inBoundary(c.x, c.y) || topLeftTree->inBoundary(d.x, d.y) || intersection(x,y,topLeftTree)) {
			topLeftTree->Find( x,  y);
		}
		if (topRightTree->inBoundary(a.x, a.y) || topRightTree->inBoundary(b.x, b.y) || topRightTree->inBoundary(c.x, c.y) || topRightTree->inBoundary(d.x, d.y) || intersection(x, y, topRightTree)) {
			topRightTree->Find( x,  y);
		}
		if (botLeftTree->inBoundary(a.x, a.y) || botLeftTree->inBoundary(b.x, b.y) || botLeftTree->inBoundary(c.x, c.y) || botLeftTree->inBoundary(d.x, d.y) || intersection(x, y, botLeftTree)) {
			botLeftTree->Find( x,  y);
		}
		if (botRightTree->inBoundary(a.x, a.y) || botRightTree->inBoundary(b.x, b.y) || botRightTree->inBoundary(c.x, c.y) || botRightTree->inBoundary(d.x, d.y) || intersection(x, y, botRightTree)) {
			botRightTree->Find( x,  y);
		}

	}

	for (int i = 0; i < this->Puntos.size(); i++) {
		if (this->Puntos[i]->x >= a.x && this->Puntos[i]->x <= d.x && this->Puntos[i]->y >= a.y && this->Puntos[i]->y <= d.y) {
			glPointSize(5);
			glBegin(GL_POINTS);
			glColor3d(1.0f, 0.0f, 0.0f);
			glVertex2d(this->Puntos[i]->x, this->Puntos[i]->y);
			glEnd();
		}
	}
}






