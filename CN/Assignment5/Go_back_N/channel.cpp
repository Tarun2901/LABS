#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <chrono> 
#include<time.h>
#include<iostream>
#include<pthread.h>
using namespace std;

#define PERMS 0644
#define TIME_PROP 2000000
#define TIMER_DUR 10 
#define WINDOWS_SIZE 4 
// TOTAL_TIME = Four times of TIME_PROP in seconds

struct my_msgbuf {
   long mtype;
   char mtext[200];
}typedef frame;


int msqid,msqid2;
frame buf3;
    

void* acks_handler(void* args){
   while(true){
         bzero(&buf3.mtext,sizeof(buf3.mtext));
         if (msgrcv(msqid2, &buf3, sizeof(buf3.mtext), 10, 0) == -1) {
            perror("msgrcv");
            exit(1);
         }
         else{
            usleep(TIME_PROP);
            printf("received from consumer: \"%s\"\n", buf3.mtext);
            int random_num = rand()%19;
            if(random_num<3){
               cout<<"************************ACK blocked\n";
               continue;
             }

         }
         // send message from Q1 to Q2
         int len = strlen(buf3.mtext);
         if (buf3.mtext[len-1] == '\n') buf3.mtext[len-1] = '\0';
         if (msgsnd(msqid, &buf3, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
         //Message sending complete in queue2
         printf("sent to Producer: \"%s\"\n ", buf3.mtext);
      }
}



int main(void) {
	srand(time(0)); 
   //For queue1 which is bw writer and channel
   frame buf;
   int len;
   key_t key;
   //For queue2 bw channel and reader
   frame buf2;
   int len2;
   key_t key2;
   system("touch msgq2.txt");
     
   
   //ftok uses the existing file name to generate a System V key -1 returned on error
   if ((key = ftok("msgq.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   //Second Q
   if ((key2 = ftok("msgq2.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }

   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
   }
   //For second Q
   if ((msqid2 = msgget(key2, PERMS | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
   }

   printf("channel ready .\n");
   buf.mtype = 1; /* we don't really care in this case */
   buf2.mtype = 1;
      
   pthread_t tid = 1;
   pthread_create(&tid,NULL,acks_handler,NULL);
   
   for(;;) { 

      for(int i=0;i<WINDOWS_SIZE-1;i++){
         bzero(&buf.mtext,sizeof(buf.mtext));
      	if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
         }
         else{
            // if(i == 0){}
            usleep(TIME_PROP);
            int random_num = rand()%19;
            // cout<<random_num<<endl;
            if(random_num<3){
   			cout<<"************************Message from writer blocked\n";
   			continue;
   		 }
            printf("received from producer: \"%s\"\n", buf.mtext);

         }
         bzero(&buf2.mtext,sizeof(buf2.mtext));
         strcpy(buf2.mtext,buf.mtext);
         
         // send message from Q1 to Q2
         len2 = strlen(buf2.mtext);
         if (buf2.mtext[len2-1] == '\n') buf2.mtext[len2-1] = '\0';

         if (msgsnd(msqid2, &buf2, len2+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
         //Message sending complete in queue2
         else{
            printf("sent to consumer: \"%s\"\n", buf2.mtext);
         }   
      }

      // HANDLING OF ACKS
   }

   printf("channel done receiving messages.\n");
   
   
   return 0;
}


