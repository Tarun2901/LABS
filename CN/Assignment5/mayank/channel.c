/* Filename: msgq_recv.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define PERMS 0644
#define SIZE 250
struct my_msgbuf {
   long mtype;
   char mtext[SIZE];
};

int main() {
    srand(time(0));
    int Tprop = 2;
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
    printf("\nTHIS IS OUR CHANNEL...\n");

    if (msgrcv(qid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
    Tprop = (int)buf.mtext[0];
    printf("Propagation delay (Tprop): %d\n\n", Tprop);
   
    while(1) { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
        // RECEIVE MESSAGE FROM SENDER
        if (msgrcv(qid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("SENDER: %s\n", buf.mtext);
        int num = (rand()%100)+1;
        printf("Random num generated is %d\n", num);
        if(num < 15) {
            printf("Dropping the message\n");
            continue;
        }
        printf("Pass on the message\n");
        // SEND MESSAGE TO RECEIVER
        buf.mtype = 2;
        int len = strlen(buf.mtext);
        sleep(Tprop);
        if (msgsnd(qid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");


        // RECEIVE ACK FROM RECEIVER
        //bzero(buf, sizeof(buf));
        struct my_msgbuf buff;
        if (msgrcv(qid, &buff, sizeof(buff.mtext), 3, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        //printf("RECEIVER(acK): %s\n\n", buff.mtext);
        printf("RECEIVER(acK)\n\n");

        // SEND ACK TO SENDER
        buff.mtype = 4;
        len = strlen(buff.mtext);
        sleep(Tprop);
        if (msgsnd(qid, &buff, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
        
    //   toend = strcmp(buf.mtext,"end");
    //   if (toend == 0)
    //   break;

    
    }
    printf("message queue: done receiving messages.\n");
   //system("rm msgq.txt");
    return 0;
}
