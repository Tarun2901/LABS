#include <stdio.h> 
#include <string.h> 
#include<signal.h> 
static volatile int keepRunning = 1;
void intHandler(int dummy) {
  printf("bye");
    keepRunning = 0; 

}
int  parse(char *line, char **argv)
{
    char *token = strtok(line, " ");
    argv[0] = token; 
    int k=1;
    while (token != NULL) 
    {
        token = strtok(NULL, " ");
        argv[k]=token;
        k++;
       
    }
    argv[k]=NULL;
  return k;                   
}


int main() 
{ 
    char  line[1024];             
    char  *argv[64];
    signal(SIGINT, intHandler);
    while (keepRunning) {
    printf("$");
    // signal(SIGINT, handle_sigint);
    // if(shut==1)
    // break; 
    gets(line);
       if (strcmp(line,"exit") == 0)
          break;
       else {
            int len= parse(line, argv);
           if (fork() == 0) {
             if (len > 0)
         { 
                   execvp(argv[0], argv);
          }
           }
          wait(NULL);
       } 
    }    
    return 0; 
} 
