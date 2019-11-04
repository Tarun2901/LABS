#include<iostream>
#include<stdio.h>
using namespace std;

int main(){
  cout<<"Inside the test function\n";
  char* str;
  fgets(str,100,stdin);
  cout << str << endl;
  int x; 
  cin >> x;
  cout <<"Exiting the function. You entered: " << x << endl;
}	

