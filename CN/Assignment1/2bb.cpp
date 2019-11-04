#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<iostream>
using namespace std;

int main(){
	int y = fork();
	if(y < 0){
		cout << "Error in fork()";
		exit(-1);
	}
	else if (y > 0){
		cout << "Inside the parent process\n";
		cout << "Waiting for the child...\n";
		int cpid = wait(NULL);
		system("ps -a -l|grep 'a.out' ");
		cout << "Child has terminated or sent a signal to the Parent\n";
		cout << "Child id: " << cpid << " Parent id: " << getpid() << " Parent's parent id: " << getppid() << endl;
		cout << "Another way to print the childId: " << y << endl;
		cout << "Exiting parent process\n";
		exit(0);
	}

	else{
		cout <<"Inside the child process\n";
		system("ps -a -l|grep 'a.out' ");
		for(int i=1;i<=10;i++)
			cout << i <<" ";
		cout <<"\nExiting the child process\n";
		//kill(getppid(),SIGKILL); 

		exit(0);
	}
}