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
#include<vector>
#include<signal.h>

using namespace std;

#define PERMS 0644
#define TIME_PROP 2000000
#define TIMER_DUR 12   // Four times of TIME_PROP in seconds
#define WINDOW_SIZE 4

struct my_msgbuf {
   long mtype;
   char mtext[200];
};

volatile __sig_atomic_t timer_expired = false;

void handle_alarm(int sig){
   cout<<"alarm ............\n";
   timer_expired = true;
}

int main(void) {
   signal(SIGALRM, handle_alarm );

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
   
   if ((msqid = msgget(key, PERMS | IPC_CREAT | IPC_NOWAIT)) == -1) { /* connect to the queue */
      perror("msgget");
      exit(1);
   }
   printf("message queue: ready to receive messages.\n");
   int ack_number = 0;
   int ack_number_received=-1;
   
   vector<int> to_receive;
   int next_ack_number;

   for(int i=0;i<WINDOW_SIZE/2;i++)
      to_receive.push_back(i);
   next_ack_number = WINDOW_SIZE/2;
   vector<int> prev_to_send;

   for(;;) {
      if(timer_expired){
         timer_expired = false;
         for(auto x:to_receive){
            string temp = "NACK " + std::to_string(x);
            strcpy(buf2.mtext,temp.c_str());

            int len = strlen(buf2.mtext);
            if (msgsnd(msqid, &buf2,len, 0) == -1) 
               perror("msgsnd error");
            else
            //Message sending complete in queue2
               printf("sent: \"%s\"\n", buf2.mtext);
         }
      }


      if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
         // EINTR is a interrupt due to signal
         if(errno == EINTR)
            continue;
         exit(1);
      }
      else{
         usleep(TIME_PROP);
         alarm(TIMER_DUR);
         cout<<"Received: "<<buf.mtext<<endl;

         stringstream ss(buf.mtext);
         string temp;
         

         ss>>temp;
         ss>>ack_number_received;
         int index=-1;
         // auto index = std::find(to_receive.begin(),to_receive.end(),ack_number_received);
         for(int i=0;i<to_receive.size();i++){
            if(to_receive[i] == ack_number_received){
               index = i; break;
            }
         }

         if(index != -1)
            to_receive.erase(to_receive.begin()+index);
         else{

         }

         if(to_receive.size() == 0){
            alarm(0);
            string temp = "ACK " + std::to_string(next_ack_number);
            strcpy(buf2.mtext,temp.c_str());

            int len = strlen(buf2.mtext);
            if (msgsnd(msqid, &buf2,len, 0) == -1) 
               perror("msgsnd error");
            else
            //Message sending complete in queue2
               printf("sent: \"%s\"\n", buf2.mtext);

            //Update the to_receive and the next_ack_number
            int count = WINDOW_SIZE/2;
            int i;
            for(i=next_ack_number;count>0;count--,i++){
               i = i%WINDOW_SIZE;
               to_receive.push_back(i);
            }
            i = i%WINDOW_SIZE;
            next_ack_number=i;
         }
       }  
      
   }
   printf("message queue: done receiving messages.\n");
   //system("rm msgq.txt");
   return 0;
}