#include <iostream>

using namespace std;

int main()
{
    float x,y,k;
    
    x = 0.1;
    y =100000;

    int i;
    while(true)
    {
        i++;
        y = x*x-3;
        x = x-y/(2*x); 

        cout << "i=" <<i<<  "  x=" <<x << " y=" << y <<endl;

        if(y>0){
            if(y<0.0001){
              break;
            }
        }
        else
        {
            if((y>-0.0001) || (y ==0)){
              break;
            }
        }
    }
}

