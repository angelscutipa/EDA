#include <iostream>
//#include "quadtree.h"
#include <time.h>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    /*srand(time(NULL));
    Qtree angel(3);
    int x, y, ran;

    for (int i = 0; i < 10; ++i)
    {
        x=rand()%300;
        y=rand()%300;
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

       cout<<"punto"<<x<<"  "<<y<<endl;

        angel.insert(x, y);
    }
    angel.print(angel.root);*/

    vector<int> a;

    for (int i = 0; i < 10; ++i)
    {
        a.push_back(i);
    }

    

    return 0;



}
/*
cmake ..
make
./hello
*/