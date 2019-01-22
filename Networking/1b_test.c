#include<unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
int main()
{
	int status,exstat;
	pid_t c1=fork();
	pid_t c2=fork();
	if(c1>0&&c2>0)
	{
		int x=waitpid(c1,&status,0);
		exstat = WEXITSTATUS(status);
		bool bl=false;
		bl=WIFEXITED(status);
		printf(" %d %d %d\n",exstat,x,bl);
		printf("Parent process\n");
		printf("%d %d \n",getpid(),getppid());
	}
	if(c1==0&&c2>0)
	{
		printf("Child 1 process\n");
		pid_t mypid   = getpid();
		_exit(2);
	}
	if(c1>0&&c2==0)
	{
		//sleep(2);
		printf("Child 2 process\n");
	}
	if(c1==0&&c2==0)
	{
		printf("Grandchild process\n");
		exit( EXIT_SUCCESS );
	}
}