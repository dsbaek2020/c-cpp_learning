/*2021/12/01
 Author : CSY
*/
#include <iostream>
using namespace std;

float y;
float x;

int main() {
 
      x = 0.1;
      y = 1000000;
    
    while(1){
          y = x*x -3;  //2Dfunc
          cout<<y<<endl;

          x = x - y/(2*x);
          cout<<x<<endl;
           cout<<"y="<<y<<endl;

          if((y<0.0001) &&(y>0)){
                break;
          }else{
              if(( y>-0.0001) && (y<0))
                   break;
              }

      }
      cout<<"y="<<y<<endl;
} 
 //return y
