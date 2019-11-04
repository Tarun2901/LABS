#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
#include <unistd.h>
#include <chrono> 
#include<sstream>
#include<iostream>
using namespace std;

#define PERMS 0644
#define TIME_PROP 2000000
#define WINDOWS_SIZE 4

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
   int ack_number = 0;
   int ack_number_received=-1;
   int flag = 0;

   for(;;) { 
      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      else{
         usleep(TIME_PROP);
         
         stringstream ss(buf.mtext);
         string temp;
         int counter = 0; 

         ss>>temp;
         ss>>ack_number_received;

         if(ack_number_received != ack_number){
            ack_number_received = ack_number;
            flag = 1;
         }

         if(flag == 0){
            ack_number = (ack_number + 1)%(WINDOWS_SIZE-1);
            cout<<"Received: " << buf.mtext << endl;
         }

       }  
      flag = 0;
      string temp = "ACK " + std::to_string(ack_number);
      strcpy(buf2.mtext,temp.c_str());

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