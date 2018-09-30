#include <iostream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;



class puntos
{
public:
    puntos(){}
    vector<double> pts;
    void set_coordenadas(double a){
        pts.push_back(a);
    }
    void give(int n){

        for (int i =0; i<n; i++){
            double a;
            a=rand();
            a=a/100;
            while(a>1){
                a=a-1;
            }
            set_coordenadas(a);
        }
    }
    void print(){
        cout<<"(";
        for (int i =0; i<pts.size(); i++){
            cout<<pts[i]<<",";
        }
    }
};

double medir_dist(puntos a, puntos b){
    double d=0;
    for(int i=0; i<a.pts.size(); i++){
        d=d+((b.pts[i]-a.pts[i])*(b.pts[i]-a.pts[i]));
    }
    d=abs(d);
    return sqrt(d);
}

class dimension
{
public:
    double minimo, maximo, promedio;

    vector<puntos> dim;
    dimension(){    }
    void set_pts(puntos a){
        dim.push_back(a);
    }
    void print(){
        for (int i =0; i<dim.size(); i++){
            dim[i].print();
            cout<<")"<<endl;
        }
    }

    void distancias(){
        vector<double> distancias;
        for(int i=0; i<dim.size();i++){
            for(int j=i; j<dim.size();j++){
                distancias.push_back(medir_dist(dim[i],dim[j]));
            }
        }
        vector<double> dist;
        this->maximo=distancias[0];
        this->minimo=distancias[0];
        this->promedio=distancias[0];
        for(int i=1; i<distancias.size();i++){
            if(distancias[i]>maximo){
                this->maximo=distancias[i];
            }
            if(distancias[i]<minimo){
                this->minimo=distancias[i];
            }
            this->promedio=this->promedio+distancias[i+1];

        }
        this->promedio=this->promedio/distancias.size();
    }



};


class prueba
{
public:
    dimension angel;
    prueba(){};
    void give(int cant_puntos){
        for(int i=0 ; i<cant_puntos; i++){
            puntos a;
            a.give(100);
            angel.set_pts(a);
        }
        angel.distancias();
        cout<<"distancia minima: "<<angel.minimo<<endl;
        cout<<"distancia maxima: "<<angel.maximo<<endl;
        cout<<"distancia promed: "<<angel.promedio<<endl;
        //angel.print();
    }

};




int main()
{
    srand(time(NULL));
    prueba uno;
    uno.give(100);
    cout << "Hello world!" << endl;
    return 0;
}
