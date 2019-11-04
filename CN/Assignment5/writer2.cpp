#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
}typedef frame;

int main(void) {
   frame buf2;
   int msqid2;
   int len2;
   key_t key2;
   system("touch msgq2.txt");
   
   //ftok uses the existing file name to generate a System V key -1 returned on error
   if ((key2 = ftok("msgq2.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
   }
   
   
   if ((msqid2 = msgget(key2, PERMS | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
   }

   buf2.mtype = 1;
   strcpy(buf2.mtext,buf.mtext);
   if (buf2.mtext[len-1] == '\n') buf2.mtext[len-1] = '\0';
   if (msgsnd(msqid2, &buf2, len2+1, 0) == -1) /* +1 for '\0' */
      perror("msgsnd");
   //Message sending complete in queue2

   if (msgctl(msqid2, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
   return 0;
}
