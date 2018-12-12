#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <vector>
//#include <GL/glut.h>
#include <math.h>
#include "kdtree.h"

using namespace std;


/*

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

*/

bool verificar_menor(punto a, punto b){
	for (int i = 0; i < a.pts.size(); ++i)
	{
		if(a.pts[i]>=b.pts[i]){
			return false;
		}
		
	}
	return true;
}
bool verificar_mayor(punto a, punto b){
	for (int i = 0; i < a.pts.size(); ++i)
	{
		if(a.pts[i]<b.pts[i]){
			return false;
		}
		
	}
	return true;
}

float medir_distancia_v(vector<float> p1, vector<float> p2){
	float rad=0;
	float suma=0;
	for (int i = 0; i < p1.size() ; ++i)
	{
		suma=suma+((p2[i]-p1[i])*(p2[i]-p1[i]));
	}
	rad=sqrt(suma);
	return rad;
}


float medir_distancia(int x1, int y1, int x2, int y2){
	float rad=0;
	rad=sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
	return rad;
}

punto media(vector<punto> ent){
	punto a;
	pair<int,int> ret;
	a.pts.push_back(0);
	a.pts.push_back(0);
	int ix, iy;
	for (int i = 0; i < ent.size(); ++i)
	{
		a.pts[0]=a.pts[0]+ent[i].pts[0];
		a.pts[1]=a.pts[1]+ent[i].pts[1];
	}
	
	ix= (a.pts[0] / 2);
	iy= (a.pts[1] / 2);

	a.pts[0]=ix;
	a.pts[1]=iy;

	return a;
}
/*
int split_eje(punto ent, nodo *p){
	vector<float> dist;
	dist.push_back(medir_distancia( ent.pts[0], ent.pts[1], ent.pts[0], (*p).ini.pts[1]));
	dist.push_back(medir_distancia( ent.pts[0], ent.pts[1], ent.pts[0], (*p).fin.pts[1]));
	dist.push_back(medir_distancia( ent.pts[0], ent.pts[1], (*p).ini.pts[0], ent.pts[1] ));
	dist.push_back(medir_distancia( ent.pts[0], ent.pts[1], (*p).fin.pts[0], ent.pts[1] ));
	if(sqrt((dist[0]-dist[1]) * (dist[0]-dist[1]) )> sqrt( (dist[2]-dist[3]) * (dist[2]-dist[3]) )) return 1;
	else return 2;
}*/

KDtree::KDtree(int cantidad_pts){
	srand(time(NULL));
	this->n=cantidad_pts;
	root=new nodo();
	
}

void KDtree:: insert(vector<punto> nuevo){
	for (int i = 0; i < nuevo.size(); ++i)
	{
		root->puntos.push_back(nuevo[i]);
		check(root);
	}
	
	
}


void KDtree::check(nodo *p){
	int tamx=((*p).fin.pts[0]-(*p).ini.pts[0])/2;
	int tamy=((*p).fin.pts[1]-(*p).ini.pts[1])/2;
	int ite=0;
	if (((*p).fin.pts[0]-(*p).ini.pts[0])*((*p).fin.pts[0]-(*p).ini.pts[0])==0.000001 || ((*p).fin.pts[1]-(*p).ini.pts[1])*((*p).fin.pts[1]-(*p).ini.pts[1])==0.000001)
	{
		return;
	}
	if ((*p).puntos.size()>this->n && !(*p).next[0])
	{
		int ind=rand()%5;												//esta parte nomas ya falta para que cambie el ind y no lo elimine
		if ((*p).puntos[0].pts[ind]==(*p).puntos[1].pts[ind]){
			(*p).puntos.erase(begin((*p).puntos) + 1);
			return;
		}
		for (int i = 0; i < 2; ++i)		{
			(*p).next[i]=new nodo();
		}
	
		float sum=0;
		sum=((*p).puntos[0].pts[ind]+(*p).puntos[1].pts[ind])/2;


		for (int i = 0; i < (*p).puntos[ind].pts.size(); ++i)
		{
			(*p).next[0]->ini.pts.push_back((*p).ini.pts[i]);
		}

		for (int i = 0; i < (*p).puntos[ind].pts.size(); ++i)
		{
			if (i==ind)
			{
				(*p).next[0]->fin.pts.push_back(sum);
				
			}
			else{
				(*p).next[0]->fin.pts.push_back((*p).fin.pts[i]); 
			}
		}

		for (int i = 0; i < (*p).puntos[ind].pts.size(); ++i)
		{
			if (i==ind)
			{
				(*p).next[1]->ini.pts.push_back(sum);
				
			}
			else{
				(*p).next[1]->ini.pts.push_back((*p).ini.pts[i]); 
			}
		}

		for (int i = 0; i < (*p).puntos[ind].pts.size(); ++i)
		{
			(*p).next[1]->fin.pts.push_back((*p).fin.pts[i]);
		}

	}

	if ((*p).next[0])
	{

		for (int i = 0; i < (*p).puntos.size(); ++i)
		{
			for (int j = 0; j < 2; ++j)
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

void KDtree::knnsearch( punto b){
	nodo* p; // es un temporal
	p=root;
	int i=0;
	while((*p).next[0]){
		for (int j = 0; j < 2; ++j)
		{
			if ( verificar_mayor( b, (*p).next[j]->ini) && verificar_menor( b, (*p).next[j]->fin))
			{
				p=(*p).next[j];
				break;
			}
		}
		cout<<i++<<endl;
	}
	cout<<"este punto es : ";(*p).puntos[0].print();
}

void KDtree::find(int rx, int ry, int rad, nodo *p, bool enter){
	float distancia[4];
	vector< nodo* > n_ver;
	for (int i = 0; i < 2; ++i)
	{
		if((*p).next[i]){ 

			distancia[0]=medir_distancia((*p).next[i]->ini.pts[0],(*p).next[i]->ini.pts[1], rx,ry );
			distancia[1]=medir_distancia((*p).next[i]->ini.pts[0],(*p).next[i]->fin.pts[1], rx,ry );
			distancia[2]=medir_distancia((*p).next[i]->fin.pts[0],(*p).next[i]->ini.pts[1], rx,ry );
			distancia[3]=medir_distancia((*p).next[i]->fin.pts[0],(*p).next[i]->fin.pts[1], rx,ry );
			
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
		for (int i = 0; i < 2; ++i)
		{
			n_ver.push_back((*p).next[i]);
		}
	}
	

	for (int i = 0; i < n_ver.size(); ++i)
	{
		find(rx,ry,rad,n_ver[i], enter);
	}	
}

void KDtree:: pintar(int x, int y, int rad, nodo *p){
	/*int rad2;
	int count=0, cantidad=(*p).puntos.size();
	for (int i = 0; i < cantidad; ++i)
	{
		rad2=sqrt(((((*p).puntos[i-count].pts[0])-x)*(((*p).puntos[i-count].pts[0])-x))+((((*p).puntos[i-count].pts[1])-y)*(((*p).puntos[i-count].pts[1])-y) ));
		if (rad2<=rad)
		{
			displayGizmoP((*p).puntos[i-count].pts[0], (*p).puntos[i-count].pts[1], 45,255,245);
		}
	}
	*/

}

void KDtree::print(nodo *p){
	/*nodo* temp;

	displayGizmo2((*p).ini.pts[0], (*p).fin.pts[0], (*p).ini.pts[1], (*p).fin.pts[1]);
	//cout<<"region"<<(*p).ini.pts[0]<<" " <<(*p).fin.pts[0]<<" "<< (*p).ini.pts[1]<<" "<< (*p).fin.pts[1];

	for (int i = 0; i < (*p).puntos.size(); ++i)
	{
		displayGizmoP((*p).puntos[i].pts[0], (*p).puntos[i].pts[1], 0,255,0);
		//cout<<"punto: "<<(*p).puntos[i].pts[0]<<"  "<<(*p).puntos[i].pts[1]<<endl;
	}
	for (int i = 0; i < 2; ++i)
	{
		if((*p).next[i]){ 
			print((*p).next[i]);
		}

	}
	*/
	
}


KDtree::~KDtree(){
	
}



