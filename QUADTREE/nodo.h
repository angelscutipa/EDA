#include <iostream>
#include <vector>

using namespace std;

class punto
{
public:
	int x, y;
	punto(){}
	~punto(){};
	
};

class nodo
{
public:
	punto ini, fin;
	vector<punto> puntos;
	nodo *next[4];
	nodo();
	virtual ~nodo();

protected:

private:
};

nodo::nodo()
{
	for (int i = 0; i < 4; ++i)
	{
		next[i]=NULL;
	}
	//ctor
}
nodo::~nodo()
{
	//dtor
}
