#include<iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(){
	// while(1){
		int pid = fork();
		if(pid < 0){
			cout<<"Not able to fork a process\n";
			exit(0);
		}
		else if(pid == 0){
			cout<<"The child process will be started";
			char* myargs[] = {"a.out"};
			execve(myargs[0],&myargs[0],);
		}
		else{
			int terminate_reason = 0;
			waitpid(-1,&terminate_reason,0);
			cout<<"Child has exited. Back in the parent process\n";
		}
	// }
}