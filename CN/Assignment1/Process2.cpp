#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include<iostream> 
using namespace std;

void forkexample() 
{ 
	int x = 1; 
	int y = fork();
	if (y == 0){ 
		cout << "I am the child Process\t" << getpid() << " " << y << endl;
	}
	else{
		cout << "I am the parent Process\t" << getpid() <<" " << y <<endl;
	}
}
 
int main() 
{ 
	forkexample(); 
	return 0; 
} 
