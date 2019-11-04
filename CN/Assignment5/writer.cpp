#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h> 
#include<iostream>
using namespace std;

#define PERMS 0644
#define TIME_PROP 200000
      
struct my_msgbuf {
   long mtype;
   char mtext[200];
}typedef frame;

int main(void) {
   frame buf,buf2;
   int msqid;
   int len;
   key_t key;
   system("touch msgq.txt");
   time_t timenow1,timenow2;

   //ftok uses the existing file name to generate a System V key -1 returned on error
   if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   
   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
   }

   printf("message queue: ready to send messages.\n");
   printf("Enter lines of text, ^D to quit:\n");
   buf.mtype = 1; /* we don't really care in this case */
   
   while(fgets(buf.mtext, sizeof (buf.mtext), stdin) != NULL) {
      buf.mtype = 1; /* we don't really care in this case */
      len = strlen(buf.mtext);
      /* remove newline at end, if it exists */
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
      if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
      perror("msgsnd");
      else{
         timenow1 = time(NULL);
         cout<<"Sent data at "<< ctime(&timenow1) << endl;
      }

      if (msgrcv(msqid, &buf2, sizeof(buf2.mtext), 10, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      else{
         usleep(TIME_PROP);
         timenow2 = time(NULL);
         cout<<"Received ACK at "<< ctime(&timenow2) << endl;
         double elapsed_seconds = difftime(timenow2,timenow1);
         cout<<"Time Elapsed: "<<elapsed_seconds<<endl;
      }

   }
   strcpy(buf.mtext, "end");
   len = strlen(buf.mtext);
   if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
   perror("msgsnd");
   
   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
   return 0;
}
