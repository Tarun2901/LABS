#include <stdio.h> 
#include <signal.h> 

void sigintHandler(int sig_num) 
{ 
	signal(SIGINT, sigintHandler); 
	printf("\n Cannot be terminated using Ctrl+C \n"); 
	fflush(stdout); 
} 

int main () 
{ 
	signal(SIGINT, sigintHandler); 
	while(1) 
	{		 
	} 
	return 0;  
} 
