// C Program to design a shell in Linux 
// -lreadline
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h> 
#include<iostream>
using namespace std;

#define MAX 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 

int child_pid = -1 ; 

void sigintHandler(int sig_num) 
{
    // signal(SIGINT, sigintHandler); 
    printf("\n Child process has been terminated \n"); 
    kill(child_pid,SIGKILL);
   // fflush(stdout); 
} 

void sigHandlerZ(int sig_num){
	if(getpid() == child_pid){
		signal(SIGTSTP, sigHandlerZ);
		cout << "Inside the child process handler";
	}

	else{
		cout <<"Putting child process to background\n";
		signal(SIGTSTP,sigintHandler);
		kill(child_pid,SIGTSTP);	
	}	
}

int takeInput(char* str) 
{ 
     char* line; 
     line = readline("\n$$ "); 
     
     if (strlen(line) != 0) { 
          strcpy(str, line);
	  if(strcmp(str,"quit") == 0){
	  	cout <<"Exiting the Shell ...\n ";
		exit(0);
	  } 
          return 0; 
     } else { 
          return 1; 
     } 
} 

void execArgs(char* parsed[]) 
{ 
     int pid = fork(); 
     child_pid = pid;

     if (pid == -1) { 
          printf("\nFailed forking child.."); 
          return; 
     } else if (pid == 0) { 
          if (execvp(parsed[0], parsed) < 0) { 
               printf("\nCould not execute command.."); 
          } 
        exit(0); 
     } else {
          wait(NULL); 
          return; 
     } 
} 

void parseSpace(char* str, char* parsed[]) 
{ 
    for (int i = 0; i < MAXLIST; i++) { 
          parsed[i] = strsep(&str, " "); 

          if (parsed[i] == NULL) 
               break; 
	} 
} 


int main() 
{ 
     char inputString[MAX], *parsedString[MAXLIST]; 
     signal(SIGINT, sigintHandler); 
     signal(SIGTSTP, sigHandlerZ);

     while (1) { 
          if (takeInput(inputString) == 1) 
               continue;
          parseSpace(inputString,parsedString);
          execArgs(parsedString);
           
     } 
     return 0; 
} 
