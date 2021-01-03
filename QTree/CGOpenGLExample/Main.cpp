#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "QuadTree.h"
#include <stdlib.h>
#include <time.h>
#define KEY_ESC 27
#define tam 1000

using namespace std;

Quad* qt;


void OnMouseClick(int button, int state, int x_, int y_)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		qt->insert(x_,y_ );
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		qt->cuadro = true;
		qt->xCuadro = x_;
		qt->yCuadro = y_;
		
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		qt->cuadro = false;
		qt->xCuadro = x_;
		qt->yCuadro = y_;
	}
}

void OnMouseMotion(int x_, int y_){
		qt->xCuadro = x_;
		qt->yCuadro = y_;

}


void idle() {
	glutPostRedisplay();
}

void glPaint(void) {

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	glOrtho(0, tam, tam, 0, -1, 1);

	qt->draw(); // DIBUJAR

	glutSwapBuffers();
}

void init_GL(void) {
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;	
	default:
		break;
	}

}


//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(tam, tam);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("QuadTree");

	init_GL();
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);


	qt = new Quad(Point(0,0), Point(tam,tam), 5);

	int a, b;
	srand(time(NULL));

	for (int i = 0; i < 0; i++) {
		a = rand() % tam;
		b = rand() % tam;
		qt->insert(a, b);
	}


	glutMainLoop(); 
	return 0;
}
