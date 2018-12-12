#include <iostream>
#include <vector>

using namespace std;

class punto
{
public:
	vector<float> pts;
	punto(){}
	void print(){
		cout<<"punto ";
		for (int i = 0; i < pts.size(); ++i)
		{
			cout<<pts[i]<<"  ";
		}
		cout<<endl;
	}
	~punto(){};
	
};

class nodo
{
public:
	punto ini, fin;
	vector<punto> puntos;
	nodo *next[2];
	nodo();
	virtual ~nodo();

protected:

private:
};

nodo::nodo()
{
	for (int i = 0; i < 2; ++i)
	{
		next[i]=NULL;
	}
	//ctor
}
nodo::~nodo()
{
	//dtor
}
