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
#include<sstream>
using namespace std;

#define PERMS 0644
#define TIME_PROP 2000000 //In micro seconds
#define TIMER_DUR 12   // Four times of TIME_PROP in seconds
#define TIME_FRAME 500000
#define WINDOWS_SIZE 4

struct my_msgbuf {
   long mtype;
   char mtext[200];
}typedef frame;


volatile __sig_atomic_t timer_expired = false;
volatile __sig_atomic_t all_ack_received  = false;
volatile __sig_atomic_t is_retransmission  = false;

void handle_alarm(int sig){
   // cout<<"alarm ............\n";
   timer_expired = true;
}

int main(void){
   signal(SIGALRM, handle_alarm );

   frame buf2;
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
   
   int frame_number = 0;
   frame buf[5];
   bool ack_received[WINDOWS_SIZE-1];
         
   while(true){
      
take_input:
      for(int i=0;i<WINDOWS_SIZE-1;i++){
         ack_received[i] = false;

         cout<<"$$$$ ";      
         fgets(buf[i].mtext, sizeof (buf[i].mtext), stdin);   
         buf[i].mtype = 1; 
         len = strlen(buf[i].mtext);
         /* remove newline at end, if it exists */
         if (buf[i].mtext[len-1] == '\n') buf[i].mtext[len-1] = '\0';

         string temp = buf[i].mtext;
         temp += +" " + std::to_string(i);
         strcpy(buf[i].mtext,temp.c_str());
      }

sender:  
          for(int i=frame_number;i<WINDOWS_SIZE-1;i++){
            if(msgsnd(msqid, &buf[i], len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
            else{
               if(!is_retransmission){
                  timenow1 = time(NULL);

               }

               is_retransmission = false;
               timer_expired = false;
               all_ack_received = false;
               alarm(TIMER_DUR);
               cout<<"Sent "<<buf[i].mtext<<" at "<< ctime(&timenow1) << endl;
            }
         }

         int count = 0;
         while(count < (WINDOWS_SIZE-1) ) {
            cout<<"waiting for acks....\n";
            if(timer_expired){
               goto sender;
            }
            else if (msgrcv(msqid, &buf2, sizeof(buf2.mtext), 10, 0) == -1) {
               // error in receiving
            }
            else{
            // timer_expired = false;
            stringstream ss(buf2.mtext);
            string temp;
            int counter = 0;

            while(ss>>temp){
               if(counter == 1){
                  ack_received[stoi(temp)] = true;
                  break;
               }
               counter ++;
            }
            cout<<"Received: " << buf2.mtext << endl;
            count ++;
           }
           for(int i=WINDOWS_SIZE-2;i>=0;i--){
               if(ack_received[i] == false)
                  continue;
               if(ack_received[i] == true){
                  frame_number = i;
                  for(int j=i-1;j>0;j--){
                     ack_received[j] = true;
                  }
                  break;
               }
            }
            count = 0;
            if(ack_received[0] && !ack_received[1])
            	ack_received[0] = false;
            
            for(int i=0;i<WINDOWS_SIZE-1;i++){
               cout<<ack_received[i]<<" ";
               if(ack_received[i])
                  count ++;
            }
            // cout<<endl<<count<<"****************************\n";
            if(count == (WINDOWS_SIZE-1))
               break;
            // if(ack_received[0] == true)
            //    break;
         }

         all_ack_received = true;
         frame_number = 0;
         
         // if(timer_expired && !all_ack_received){
         //       cout<<"*****"; 
         //       timer_expired = false; all_ack_received = false; is_retransmission = true;
         //       goto sender;
         // }
      }

   return 0;
}
