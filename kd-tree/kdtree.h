#ifndef MYHEADER
#define MYHEADER


#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "nodo.h"
#include <math.h>

using namespace std;

class KDtree
{
public:
	nodo* root;
	int n;
	void insert(vector<punto> nuevo);
	
	void check(nodo *p);
	KDtree(int cantidad_pts);
	void print(nodo *p);
	void find(int rx, int ry, int rad, nodo *p, bool enter);
	void pintar(int x, int y, int rad, nodo *p);
	void knnsearch( punto b);
	~KDtree();
	
};


#endif 