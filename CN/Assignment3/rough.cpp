#include <stdlib.h>
#include<iostream>
using namespace std;

int main(void) {
    int a[5] = {1,2,3,4,5};
    int *b = a;
    for(int i=0;i<6;i++){
    	cout << b <<" " << *b << endl;
	b++;
    }		    
   // int exit_status = system("gnome-terminal");
    cout<<"Hello from parent";
}
