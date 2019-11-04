#include <sys/types.h> 
#include <unistd.h>
#include<iostream> 
using namespace std;
#define SIZE 16

int main(){
	char* m1 = "First Message";
	char* m2 = "Second Message";

	char input[SIZE];
	int p[2];

	if(pipe(p) < 0)
		exit(1);

	write(p[1],m1,SIZE);
	write(p[1],m2,SIZE);

	for(int i=0;i<2;i++){
		cout << p[0] << endl;
		read(p[0],input,SIZE);
		cout << input << endl;
	}

}
