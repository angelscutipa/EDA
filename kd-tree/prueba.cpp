#include <iostream>
#include "kdtree.cpp"
#include <time.h>
#include <vector>
#include <thread>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

using namespace std;

float x_disp, y_disp;

int x_dis, y_dis;

bool i_circle;

int i_x, i_y, rad;

int d_x_min,d_x_max,d_y_min,d_y_max; 

int mod_x, mod_y;

vector<pair<int,int>> lista_puntos;

punto p_min, p_max, p_med;

vector< punto > leer_datos(){
  ifstream  data("data_set.txt");
  string::size_type sz;
  vector<string> leidos;
    vector< punto > lista;
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

    

  //min.first=10000; min.second=10000;

    for (int i = 0; i < 90; ++i)
    {
      p_min.pts.push_back(10000);
    }

    //max.first=-10000; max.second=-10000;

    for (int i = 0; i < 90; ++i)
    {
        p_max.pts.push_back(-10000);
    }

    for (int i = 0; i < 90; ++i)
    {
      p_med.pts.push_back(0);
    }

    float number=0;

    for (int i = 0; i < leidos.size(); ++i)
    {
      punto coord;
      leido=leidos[i];
      for (int j = 0; j < leido.size(); ++j)
      {
        if( leido[j]==',' ){
          coord.pts.push_back( stof (p_x,&sz) );
          p_x="";
          continue;
        }
        else{
          p_x=p_x+leido[j];
        }
      }
            
      lista.push_back(coord);

      number=medir_distancia_v(coord.pts, p_med.pts);
      if (number<medir_distancia_v(p_min.pts, p_med.pts)){
        p_min.pts=coord.pts;
      }
      else if(number>medir_distancia_v(p_max.pts, p_med.pts)) p_max.pts=coord.pts;
    }



/*for (int i = 0; i < lista.size(); ++i)
    {
      cout<<lista[i].pts.size()<<endl;
      for (int j = 0; j < lista[i].pts.size(); ++j)
      {
        cout<<lista[i].pts[j]<<"|";
      }
      cout<<endl;
        
    }*/
    

    d_x_min=p_min.pts[0];
    d_y_min=p_min.pts[1];

    d_x_max=p_max.pts[0];
    d_y_max=p_max.pts[1];

    mod_x=d_x_max-d_x_min;
    mod_y=(d_y_max-d_y_min)*(-1);

    return lista;
} 

class Rkdtree
{
public:
    int num_arboles;
    vector< KDtree > bosque;
    Rkdtree(int a){num_arboles=a;};

    void build(){
        for (int i = 0; i < num_arboles; ++i)
        {
            KDtree angel(1);
            angel.root->ini.pts.push_back(d_x_min);
            angel.root->ini.pts.push_back(d_y_max);
            for (int j = 2; j < 90; ++j)
            {
                angel.root->ini.pts.push_back(p_min.pts[j]);
            }
            angel.root->fin.pts.push_back(d_x_max);
            angel.root->fin.pts.push_back(d_y_min);
            for (int j = 2; j < 90; ++j)
            {
                angel.root->fin.pts.push_back(p_max.pts[j]);
            }
            bosque.push_back(angel);
        }
    }

    void insert_data(vector<punto> entrada);
    void search_data(punto entrada);

    ~Rkdtree(){};
};


void Rkdtree::insert_data(vector<punto> entrada){
    //thread t_arbol[num_arboles];
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    for (int i = 0; i < num_arboles; ++i)
    {
        bosque[i].insert(entrada);
    }
    /*
    for (int i = 0; i < num_arboles; ++i)
    {
        t_arbol[i]=thread(bosque[i].insert, entrada);
    }
    for (int i = 0; i < num_arboles; ++i)
    {
        t_arbol[i].join();
    }*/

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time insertion:       %.28f s\n", tiempo/1000);

}

void Rkdtree::search_data(punto entrada){
    //thread t_arbol[num_arboles];
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    for (int i = 0; i < num_arboles; ++i)
    {
        bosque[i].knnsearch(entrada);
    }
    /*
    for (int i = 0; i < num_arboles; ++i)
    {
        t_arbol[i]=thread(bosque[i].insert, entrada);
    }
    for (int i = 0; i < num_arboles; ++i)
    {
        t_arbol[i].join();
    }*/

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time search_data:       %.28f s\n", tiempo/1000);

}

int main(int argc, char** argv)
{
    vector< punto > nusm;

    nusm=leer_datos();
    cout<<"termine de leer"<<endl;

    Rkdtree a_bosque(5);
    a_bosque.build();
    a_bosque.insert_data(nusm);
    int a; cin>>a;
    //a_bosque.search_data(nusm[10000]);

    return 0;

}
/*
cmake ..
make
./hello
*/