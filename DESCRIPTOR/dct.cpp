#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include "cpt.cpp"

using namespace std;
using namespace cv;

class pos {
	public:
		int x, y;
		Vec3b color;
		pos(int a, int b, Vec3b c) {
			x = a;
			y = b;
			color = c;
		}

};

vector< int > pintar(Mat *img, int xi, int yi, int xf, int yf) {
	vector<pos> pintar;
	Vec3b color;
	int r=0, g=0, b=0;
	color[0]=0;
	color[1]=0;
	color[2]=0;
	int cont=0;
	for (int i = xi; i < xf; i++) {
		for (int j = yi; j < yf; j++) {
			r=r+(int)(*img).at<Vec3b>(i, j)[0];
			g=g+(int)(*img).at<Vec3b>(i, j)[1];
			b=b+(int)(*img).at<Vec3b>(i, j)[2];
			cont++;
		}
	}
	r=r/cont;

	g=g/cont;
	b=b/cont;

	vector<int> rgb;
	rgb.push_back(r);
	rgb.push_back(g);
	rgb.push_back(b);

	return rgb;

}

vector< vector<int> > dividir(Mat *img){
	vector< vector<int> > rpt;
	int x, y;
	int comp=4;
	x=(*img).rows/comp;
	y=(*img).cols/comp;
	for (int i = 0; i < comp; ++i)
	{
		for (int j = 0; j < comp; ++j)
		{
			if (j==comp-1 and i==comp-1) rpt.push_back(pintar(img, x*j,y*i,(*img).rows,(*img).cols));
			else if (j==comp-1) rpt.push_back(pintar(img, x*j,y*i,(*img).rows,y*(i+1)));
			else if (i==comp-1) rpt.push_back(pintar(img, x*j,y*i,x*(j+1),(*img).cols));
			else rpt.push_back(pintar(img, x*j,y*i,x*(j+1),y*(i+1)));
		}	
	}

	/*for (int i = 0; i < rpt.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cout<<rpt[i][j]<<" ";
		}
		cout<<endl;
	}*/
	return rpt;
}


int main() {

	vector<string> carpetas;
	carpetas=optener_carpetas("./imagenes");

	ofstream fs("px_concat.txt");

	Mat img2;
	namedWindow("image",WINDOW_NORMAL);
	

	/*for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			(*imagen).at<uint8_t>(i, j) = 0;
		}
	}*/
	vector< vector<int> > rpt;

	struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);
    for (int i = 0; i < carpetas.size(); ++i)
    {
    	vector<string> archivos;
    	string ruta="./imagenes/"+carpetas[i];

    	char *y = new char[ruta.length() + 1]; // or
		std::strcpy(y, ruta.c_str());

    	archivos=optener_archivos(y);
    	for (int j = 0; j < archivos.size(); ++j)
    	{
    		string ruta2=ruta+"/"+archivos[j];
    		Mat img = imread(ruta2,CV_LOAD_IMAGE_UNCHANGED);
			Mat *imagen = &img;
			rpt=dividir(imagen);
			for (int i = 0; i < rpt.size(); ++i)
			{
				fs << rpt[i][0] <<" ";
				fs << rpt[i][1] <<" ";
				fs << rpt[i][2] <<" ";
			}
			img2=img;
			fs<<endl;
    	}
	    	
    }

	    
	


  	gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time insertion:       %.28f s\n", tiempo/1000);

    /*int dim=4;

    Mat imagen2(dim,dim,CV_8UC3);
   	
   	int cont_pixel=0;
   	cout<<rpt.size()<<endl;

    for (int i = 0; i < dim; ++i)
    {
    	for (int j = 0; j < dim; ++j)
    	{

    		imagen2.at<Vec3b>(i,j)[0] = (uchar)rpt[cont_pixel][0];
    		imagen2.at<Vec3b>(i,j)[1] = (uchar)rpt[cont_pixel][1];
    		imagen2.at<Vec3b>(i,j)[2] = (uchar)rpt[cont_pixel][2];
    		cont_pixel++;
    	}
    }*/
    imshow("image", img2);

	waitKey(0);
	return 0;
}

/*g++  dct.cpp -O3 `pkg-config --cflags --libs opencv`     /// PARA COMPILAR


Mat src = imread("../images/a.png", CV_LOAD_IMAGE_UNCHANGED);
     if (src.empty()){
          cout << "Error : Image cannot be loaded..!!" << endl;
          return 0;
     }


Vec3b a;
a[0] = 0;
a[1] = 0;
a[2] = 0;
cout << "rows: " << src.rows << endl;
cout << "cols: " << src.cols << endl;
for(int i=0; i<src.rows; i++){
for(int j=0; j<src.cols; j++){
    //if((int)(src.at<Vec3b>(i, j))[0]==0)
    (src.at<Vec3b>(i, j)) = a;
}
}*/