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
#include<vector>
using namespace std;

#define PERMS 0644
#define TIME_PROP 2000000 //In micro seconds
#define TIMER_DUR 12   // Four times of TIME_PROP in seconds
#define TIME_FRAME 500000
#define WINDOW_SIZE 4

struct my_msgbuf {
   long mtype;
   char mtext[200];
}typedef frame;


volatile __sig_atomic_t timer_expired = false;
volatile __sig_atomic_t all_ack_received  = false;
volatile __sig_atomic_t is_retransmission  = false;
bool take_input = true;

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
   vector<int> to_send;


   for(int i=0;i<WINDOW_SIZE/2;i++)
         to_send.push_back(i);
      
   while(true){
      
	if(take_input){
      
      for(int i=0;i<WINDOW_SIZE;i++){
         // if(i<WINDOW_SIZE/2)
         //    to_send.push_back(i);
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
   }   

sender:  
          for(int i:to_send){
            if(msgsnd(msqid, &buf[i], len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
            else{
               if(!is_retransmission){
                  timenow1 = time(NULL);

               }
               timer_expired = false;
               alarm(TIMER_DUR);
               cout<<"Sent "<<buf[i].mtext<<" at "<< ctime(&timenow1) << endl;
            }
        }

         while(true) {
            cout<<"waiting for acks....\n";
            if(timer_expired){
               goto sender;
            }
            else if (msgrcv(msqid, &buf2, sizeof(buf2.mtext), 10, 0) == -1) {
               // error in receiving
            }
            else{

            to_send.clear();   
            timer_expired = false;
            stringstream ss(buf2.mtext);
            string temp;
            
            if(ss>>temp){
               if(temp == "NACK"){
               	ss>>temp;
                  to_send.push_back(stoi(temp));
                  break;
               }
               else{
                  ss>>temp;
                  int sfm = stoi(temp);
                  cout<<sfm<<endl;
                  if(sfm == 0){
                     take_input = true;
                  }
                  else take_input = false;

                  int count = WINDOW_SIZE/2;
                  for(int i=sfm%WINDOW_SIZE;count>0;count--,i++){
                     i = i%WINDOW_SIZE;
                     to_send.push_back(i);
                  }
                  break;
               }
               cout<<"Received: " << buf2.mtext << endl;
              
            }
            
           }
        }
      }

   return 0;
}
