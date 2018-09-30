#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "nodo.h"
#include <math.h>

using namespace std;

void displayGizmo2(int xi, int xf, int yi, int yf){
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(xi, yi);
	glVertex2d(xf, yi);

	glColor3d(255,0,0);
	glVertex2d(xi, yf);
	glVertex2d(xi, yi);

	glColor3d(255,0,0);
	glVertex2d(xf, yi);
	glVertex2d(xf, yf);

	glColor3d(255,0,0);
	glVertex2d(xf, yf);
	glVertex2d(xi, yf);

	glEnd();
}
void displayGizmoP(int x, int y, int r, int g, int b){
	glPointSize(2);
	glBegin(GL_POINTS);

	glColor3f(r,g,b);
    glVertex2d(x,y);
    glEnd();
}



void displayGizmoC(int cx, int cy, int r){
	glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < 300; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(300);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glColor3d(0,255,0);
        glVertex2d(x + cx, y + cy); 
    }
    glEnd();
}


bool verificar_menor(punto a, punto b){
	if((a.x<b.x) && (a.y<b.y)) return true;
	return false;
}
bool verificar_mayor(punto a, punto b){
	if((a.x>b.x) && (a.y>b.y)) return true;
	return false;
}

float medir_distancia(int x1, int y1, int x2, int y2){
	float rad=0;
	rad=sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
	return rad;
}

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

Qtree::Qtree(int cantidad_pts){
	this->n=cantidad_pts;
	root=new nodo();
	


}

void Qtree:: insert(int a, int b){
	punto nuevo;
	nuevo.x=a;
	nuevo.y=b;
	this->root->puntos.push_back(nuevo);
	check(root);
	
}

void Qtree::find(int rx, int ry, int rad, nodo *p, bool enter){
	float distancia[4];
	vector< nodo* > n_ver;
	for (int i = 0; i < 4; ++i)
	{
		if((*p).next[i]){ 

			distancia[0]=medir_distancia((*p).next[i]->ini.x,(*p).next[i]->ini.y, rx,ry );
			distancia[1]=medir_distancia((*p).next[i]->ini.x,(*p).next[i]->fin.y, rx,ry );
			distancia[2]=medir_distancia((*p).next[i]->fin.x,(*p).next[i]->ini.y, rx,ry );
			distancia[3]=medir_distancia((*p).next[i]->fin.x,(*p).next[i]->fin.y, rx,ry );
			
			if (distancia[0]<=rad || distancia[1]<=rad || distancia[2]<=rad || distancia[3]<=rad )
			{
				enter=false;
				n_ver.push_back((*p).next[i]);
			}
		}
		else{
			this->pintar(rx,ry,rad,p);
		}

	}

	if (enter && (*p).next[0])
	{
		for (int i = 0; i < 4; ++i)
		{
			n_ver.push_back((*p).next[i]);
		}
	}
	

	for (int i = 0; i < n_ver.size(); ++i)
	{
		find(rx,ry,rad,n_ver[i], enter);
	}	
}

void Qtree:: pintar(int x, int y, int rad, nodo *p){
	int rad2;
	int count=0, cantidad=(*p).puntos.size();
	for (int i = 0; i < cantidad; ++i)
	{
		rad2=sqrt(((((*p).puntos[i-count].x)-x)*(((*p).puntos[i-count].x)-x))+((((*p).puntos[i-count].y)-y)*(((*p).puntos[i-count].y)-y) ));
		if (rad2<=rad)
		{
			displayGizmoP((*p).puntos[i-count].x, (*p).puntos[i-count].y, 45,255,245);
		}
	}
	

}

void Qtree:: colorear(int x, int y, int rad, nodo *p){
	int rad2;
	int count=0, cantidad=(*p).puntos.size();
	for (int i = 0; i < cantidad; ++i)
	{
		rad2=sqrt(((((*p).puntos[i-count].x)-x)*(((*p).puntos[i-count].x)-x))+((((*p).puntos[i-count].y)-y)*(((*p).puntos[i-count].y)-y) ));
		if (rad2<=rad)
		{
			displayGizmoP((*p).puntos[i-count].x, (*p).puntos[i-count].y, 45,255,245);
		}
	}
	
	for (int i = 0; i < 4; ++i)
	{
		if((*p).next[i]){ 
			colorear(x,y,rad,(*p).next[i]);
		}

	}	  	
}

void Qtree:: revisar(nodo *p, bool ver){
	if (!(*p).next[0])
	{
		return;
	}

	if (!((*p).next[0]->next[0]))
	{
		cout<<"hola"<<endl;
		int cant_pts_hijos=0;
		for (int i = 0; i < 4; ++i)
		{
			cant_pts_hijos+=(*p).next[i]->puntos.size();
		}
		if (cant_pts_hijos<=this->n)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < (*p).next[i]->puntos.size(); ++j)
				{
					(*p).puntos.push_back((*p).next[i]->puntos[j]);
				}
				(*p).next[i]->puntos.clear();
			}
			for (int i = 0; i < 4; ++i)
			{
				delete((*p).next[i]);
				ver=false;
			}
		}
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		if(!(*p).next[i]){ 
			return;
		}
		else {
			cout<<"este"<<endl;
			revisar((*p).next[i], true);
		}
	}
}

void Qtree::check(nodo *p){
	int tamx=((*p).fin.x-(*p).ini.x)/2;
	int tamy=((*p).fin.y-(*p).ini.y)/2;
	int ite=0;
	if (((*p).fin.x-(*p).ini.x)*((*p).fin.x-(*p).ini.x)==0.000001 || ((*p).fin.y-(*p).ini.y)*((*p).fin.y-(*p).ini.y)==0.000001)
	{
		return;
	}
	if ((*p).puntos.size()>this->n && !(*p).next[0])
	{
		for (int i = 0; i < 4; ++i)
		{
			(*p).next[i]=new nodo();
			
		}
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				(*p).next[ite]->ini.x=(*p).ini.x+(tamx*j);
				(*p).next[ite]->ini.y=(*p).ini.y+(tamy*i);
				(*p).next[ite]->fin.x=(*p).ini.x+(tamx*(j+1));
				(*p).next[ite]->fin.y=(*p).ini.y+(tamy*(i+1));
				ite++;
			}
		}
	}

	if ((*p).next[0])
	{

		for (int i = 0; i < (*p).puntos.size(); ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if ( verificar_mayor( (*p).puntos[i], (*p).next[j]->ini) && verificar_menor( (*p).puntos[i], (*p).next[j]->fin))
				{
					(*p).next[j]->puntos.push_back((*p).puntos[i]);
					check((*p).next[j]);
				}
			}	
		}
		(*p).puntos.clear();

	}

}


void Qtree::print(nodo *p){
	nodo* temp;

	displayGizmo2((*p).ini.x, (*p).fin.x, (*p).ini.y, (*p).fin.y);

	for (int i = 0; i < (*p).puntos.size(); ++i)
	{
		displayGizmoP((*p).puntos[i].x, (*p).puntos[i].y, 0,255,0);
	}
	for (int i = 0; i < 4; ++i)
	{
		if((*p).next[i]){ 
			print((*p).next[i]);
		}

	}
	
	
}


Qtree::~Qtree(){
	
}