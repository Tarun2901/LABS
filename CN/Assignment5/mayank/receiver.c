/* Filename: msgq_recv.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644
#define SIZE 250
struct my_msgbuf {
   long mtype;
   char mtext[SIZE];
};

int main() {
   struct my_msgbuf buf;
   int qid;
   int toend;
   key_t key;
   
   if ((key = ftok("may", 69)) == -1) {
      perror("ftok");
      exit(1);
   }
   
   if ((qid = msgget(key, PERMS)) == -1) { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
   printf("\nI AM THE RECEIVER...\n\n");
   
    while(1) { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
        if (msgrcv(qid, &buf, sizeof(buf.mtext), 2, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("SENDER sent: %s\n", buf.mtext);
        
    //   toend = strcmp(buf.mtext,"end");
    //   if (toend == 0)
    //   break;

        // SEND ACK TO SENDER
        char *d = "ACK";
        strcpy(buf.mtext, d);
        buf.mtype = 3;
        int len = strlen(buf.mtext);
        if (msgsnd(qid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
         else
            printf("ACK sent\n\n");
   }
   printf("message queue: done receiving messages.\n");
   //system("rm msgq.txt");
   return 0;
}
