#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
#include <unistd.h>
#include <chrono> 


#define PERMS 0644
#define TIME_PROP 200000


struct my_msgbuf {
   long mtype;
   char mtext[200];
};

int main(void) {
   struct my_msgbuf buf;
   int msqid;
   int toend;
   key_t key;
   
   struct my_msgbuf buf2;
   buf2.mtype = 10;
   strcpy(buf2.mtext,"ACK");

   if ((key = ftok("msgq2.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   
   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
   printf("message queue: ready to receive messages.\n");
   
   for(;;) { 
      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      else{
         usleep(TIME_PROP);
         printf("received: \"%s\"and ACK sent\n", buf.mtext);
      }
      

      int len = strlen(buf2.mtext);
      if (msgsnd(msqid, &buf2,len, 0) == -1) 
         perror("msgsnd error");
      //Message sending complete in queue2
      printf("sent: \"%s\"\n", buf2.mtext);
      
   }
   printf("message queue: done receiving messages.\n");
   //system("rm msgq.txt");
   return 0;
}