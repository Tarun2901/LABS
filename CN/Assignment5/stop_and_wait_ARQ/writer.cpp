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
#include<signal.h>
#include<pthread.h>
using namespace std;

#define PERMS 0644
#define TIME_PROP 2000000 //In micro seconds
#define TIMER_DUR 10   // Four times of TIME_PROP in seconds

struct my_msgbuf {
   long mtype;
   char mtext[200];
}typedef frame;


volatile __sig_atomic_t timer_expired = false;
volatile __sig_atomic_t ack_received  = false;
volatile __sig_atomic_t is_retransmission  = false;



void handle_alarm( int sig ) {
   timer_expired = true;
}

int main(void) {
   signal( SIGALRM, handle_alarm );

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

   
   while(fgets(buf.mtext, sizeof (buf.mtext), stdin) != NULL){
      
      buf.mtype = 1; /* we don't really care in this case */
      len = strlen(buf.mtext);
      /* remove newline at end, if it exists */
      if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

sender:  if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
         perror("msgsnd");
         else{
            if(!is_retransmission){
               timenow1 = time(NULL);

            }

            is_retransmission = false;
            ack_received = false;
            timer_expired = false;
            alarm(TIMER_DUR);
            cout<<"Sent "<<buf.mtext<<" at "<< ctime(&timenow1) << endl;
         }

      if (msgrcv(msqid, &buf2, sizeof(buf2.mtext), 10, 0) == -1) {
         // perror("msgrcv");
         // exit(1);
      }
      else{
         usleep(TIME_PROP);
         timenow2 = time(NULL);
         
         timer_expired = false;
         ack_received = true;

         cout<<"Received ACK at "<< ctime(&timenow2) << endl;
         double elapsed_seconds = difftime(timenow2,timenow1);
         cout<<"Time Elapsed: "<<elapsed_seconds<<endl;
      }

      if(timer_expired && !ack_received){
            cout<<"*****"; 
            timer_expired = false; ack_received = false; is_retransmission = true;
            goto sender;
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
