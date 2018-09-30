#define GLUT_DISABLE_ATEXIT_HACK
//#include <windows.h>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "quadtree.cpp"

//#include <quadTree.h>
#define KEY_ESC 27

using namespace std;

//Crear quad tree

Qtree angel(10);

float x_disp, y_disp;

int x_dis, y_dis;

bool i_circle;

int i_x, i_y, rad;

int d_x_min,d_x_max,d_y_min,d_y_max; 

int mod_x, mod_y;

vector<pair<int,int>> lista_puntos;


vector< pair<float,float> > read_datos(){
	ifstream file_leido("capitals.txt");
	string leido;
	vector<string> leidos;
   	vector< pair<float,float> > lista;
	int n=0;
   	while(n<246){
	    file_leido>>leido;
	    leidos.push_back(leido);
	    //cout<<leido<<endl;
	    n++;
   	}
   	int comas=0;
   	string p_x="", p_y="";

   	pair<float,float> min, max;
   	min.first=10000; min.second=10000;
   	max.first=-10000; max.second=-10000;
   	float number=0;

   	for (int i = 1; i < leidos.size(); ++i)
   	{
   		pair <float,float> coord;
   		leido=leidos[i];
   		for (int j = 0; j < leido.size(); ++j)
   		{
   			if(leido[j]==','){
   				comas++;
   				continue;
   			}
   			if (comas==2)
   			{
   				p_x=p_x+leido[j];
   			}
   			if (comas==3)
   			{
   				p_y=p_y+leido[j];
   			}
   		}
   		comas=0;
   		
  		string::size_type sz;     // alias of size_t

  		coord.first=stof (p_x,&sz);

  		string::size_type sy;     // alias of size_t

  		coord.second=stof (p_y,&sy);

   		p_x="";p_y="";
   		cout<<i<<" --> "<<coord.first<<"          "<<coord.second<<endl;
   		lista.push_back(coord);

   		if (coord.first<min.first)
   		{
   			min.first=coord.first;
   		}
   		else if (coord.second<min.second)
   		{
   			min.second=coord.second;
   		}
   		else if (coord.first>max.first)
   		{
   			max.first=coord.first;
   		}
   		else if (coord.second>max.second)
   		{
   			max.second=coord.second;
   		}
   	}

   	cout<<"min: "<<min.first<<"  "<<min.second<<endl;
   	cout<<"max: "<<max.first<<"  "<<max.second<<endl;

   	d_x_min=-200;
   	d_y_min=200;

   	d_x_max=200;
   	d_y_max=-200;

   	mod_x=d_x_max-d_x_min;
   	mod_y=(d_y_max-d_y_min)*(-1);


   	return lista;
}

vector< pair<float,float> > read_crime(){
	ifstream  data("crime50k.csv");

	vector<string> leidos;
   	vector< pair<float,float> > lista;
   	int n=0;

    string line, leido;
    while(getline(data,line))
    {
	    leidos.push_back(line);
   	}
   	int comas=0, n_1, n_2;
   	n_1=19; n_2=20;
   	int cont=0;
   	string p_x="", p_y="";

   	pair<float,float> min, max;
   	min.first=10000; min.second=10000;
   	//max.first=-10000; max.second=-10000;
   	float number=0;

   	for (int i = 120; i < leidos.size(); ++i)
   	{
   		pair <float,float> coord;
   		leido=leidos[i];
   		for (int j = 0; j < leido.size()-2; ++j)
   		{
   			if((leido[j]=='"' && leido[j+1]=='(') || ((j>leido.size()-25) && leido[j]==',' )){
   				comas++;
   				j++;
   				continue;
   			}
   			
   			if (comas==1)
   			{
   				p_x=p_x+leido[j];
   			}
   			if (comas==2)
   			{
   				p_y=p_y+leido[j];
   			}
   		}
   		comas=0;
   		
  		string::size_type sz;     // alias of size_t

  		coord.first=stof (p_x,&sz);

  		string::size_type sy;     // alias of size_t

  		coord.second=stof (p_y,&sy);

   		p_x="";p_y="";
   		coord.first=coord.first-41;
   		coord.second=coord.second+87;
   		coord.first=coord.first*10000;
   		coord.second=coord.second*10000;
   		
   		lista.push_back(coord);

   		number=medir_distancia(coord.first, coord.second, 0,0);
   		if (number<medir_distancia(min.first,min.second,0,0))
   		{
   			min=coord;
   		}
   		else if(number>medir_distancia(max.first,max.second,0,0)) max=coord;
   	}

   	cout<<"min: "<<min.first<<"  "<<min.second<<endl;
   	cout<<"max: "<<max.first<<"  "<<max.second<<endl;

   	d_x_min=min.first;
   	d_y_min=min.second;

   	d_x_max=max.first;
   	d_y_max=max.second;

   	mod_x=d_x_max-d_x_min;
   	mod_y=(d_y_max-d_y_min)*(-1);


   	return lista;



}


//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(0, 0);
	glVertex2d(300, 0);

	glColor3d(255,0,0);
	glVertex2d(0, 0);
	glVertex2d(-300, 0);

	glColor3d(255, 0, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 300);

	glColor3d(255, 0, 0);
	glVertex2d(0, 0);
	glVertex2d(0, -300);

	glEnd();
}



void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
  
  	x=(x*mod_x/600)+d_x_min;
	y=-(y*mod_y/600)+d_y_min;


    cout<<"mouse pos: "<<x<<" - "<<y<<endl;

    angel.insert(x,y);
    angel.print(angel.root);
    //angel.find(i_x,i_y,rad, angel.root);
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {

  	x=(x*mod_x/600)+d_x_min;
	y=-(y*mod_y/600)+d_y_min;


  	pair<int,int> p_a;
  	p_a.first=x;
  	p_a.second=y;

  	lista_puntos.push_back(p_a);

  	if (lista_puntos.size()==2)
  	{
  		i_circle=true;
	  	i_x=lista_puntos[0].first;
	  	i_y=lista_puntos[0].second;
	  	rad=sqrt((((lista_puntos[1].first)-(lista_puntos[0].first))*((lista_puntos[1].first)-(lista_puntos[0].first)))+(((lista_puntos[1].second)-(lista_puntos[0].second))*((lista_puntos[1].second)-(lista_puntos[0].second)) ));
	  	cout<<"punto 1: "<<lista_puntos[0].first<<" ; "<<lista_puntos[0].second<<endl;
	  	cout<<"punto 2: "<<lista_puntos[1].first<<" ; "<<lista_puntos[1].second<<endl;
	  	cout<<"radio: "<<rad<<endl;
	  	lista_puntos.clear();
	  	
	  	//angel.revisar(angel.root, true);
  	}
  }
}

void OnMouseMotion(int x, int y)
{	
	x=(x*mod_x/600)+d_x_min;
	y=-(y*mod_y/600)+d_y_min;

	i_x=x;
	i_y=y;
     //opcional 
	 //hacer algo x,z cuando se mueve el mouse
}



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(d_x_min,  d_x_max, d_y_max, d_y_min, -1.0f, 1.0f);
    
	//glOrtho(x_disp*(-1),  x_disp, y_dis*(-1), y_dis, -1.0f, 1.0f);
    

	//dibujar quadTree (qt->draw())

	
    angel.print(angel.root);
    if (i_circle==true)
    {
    	displayGizmoC(i_x, i_y, rad);
    	angel.find(i_x,i_y,rad, angel.root, true);
    }


	//dibuja el gizmo
	//displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
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
//
//el programa principal
//
int main(int argc, char** argv) {

	//medir_distancia(3,3,4,4);

	/*
	srand(time(NULL));
    
    int x, y, ran;

    vector<pair<int, int>> pts;
    pair<int, int> ps;

    for (int i = 0; i < 100000; ++i)
    {

        x=rand()%200;
        y=rand()%200;
        ran=rand()%4;
        if (ran==1)
        {
            x=-x;
        }
        else if (ran==2)
        {
            y=-y;
        } 
        else if (ran==3)
        {
            x=-x;
            y=-y;
        }
        ps.first=x;
        ps.second=y;

       //cout<<"punto"<<x<<"  "<<y<<endl;
        pts.push_back(ps);
        
    } 
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    for (int i = 0; i < pts.size(); ++i)
    {
    	angel.insert(pts[i].first, pts[i].second);
    }
    
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time insertion:       %.28f s\n", tiempo/1000);   

    */


	x_dis=300; y_dis=300;
	x_disp=300; y_disp=300;
	vector< pair<float,float> > num;
    num=read_crime();

	struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    angel.root->ini.x=d_x_min;
	angel.root->ini.y=d_y_max;
	angel.root->fin.x=d_x_max;
	angel.root->fin.y=d_y_min;

    for (int i = 0; i < num.size(); ++i)
    {
    	//cout<<"--> "<<num[i].first<<"  "<<num[i].second<<endl;
    	angel.insert(num[i].first, num[i].second);
    }
    
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time insertion:       %.28f s\n", tiempo/1000);


	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP2 bis OpenGL : Bresenham"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);

	
	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}