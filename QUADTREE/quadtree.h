#ifndef MYHEADER
#define MYHEADER


#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "nodo.h"
#include <math.h>

using namespace std;

class Qtree
{
public:
	nodo* root;
	int n;
	void insert(int a, int b);
	void colorear(int x, int y, int rad, nodo *p);
	void pintar(int x, int y, int rad, nodo *p);
	void revisar(nodo *p, bool ver);
	void check(nodo *p);
	void find(int x, int y, int rad, nodo *p, bool enter);
	Qtree(int cantidad_pts);
	void print(nodo *p);
	~Qtree();
	
};


#endif 