#include<iostream>
#include "auxFile.h"
#include "myop.h"
using namespace std;

int main(){
  int a = 5; int b = 10;
  myop(a,b);
  cout << "result is: " << result << endl;
  square(b);
  cout << "result is: " << result << endl;
  return 0;	  
}	
