#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <sys/msg.h>
#include<pthread.h>
#include<unistd.h>

struct msgbuf {
   long mtype;
   char mtext[200];
   int seqNum;
};


int received = 0, isAlive = 0, notSent = 1;
float Tframe = 1, Tprop = 2;
int msqid, started = 0;
volatile int msgFlg = 0;


void* input(void *arg) { 
    isAlive = 1;
    printf("isAlive = 11\n");
    int time = 2*(Tframe + Tprop);
    sleep(time);
    isAlive = 0;
    printf("isAlive = 00\n");
}
// if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1)
void* rec(void *arg) { 
    started = 1;
    struct msgbuf buffAck;
    printf("Trying to recceive\n");
    if (msgrcv(msqid, &buffAck, sizeof(buffAck.mtext), 4, 0) == -1) {
        perror("msgrcv error");
        exit(1);
    }
    received = 1;
    printf("recvdACK: %s\n", buffAck.mtext);
}

void startTimer() {
    pthread_t p;
    if(pthread_create(&p,NULL,&input,NULL) != 0) {
        printf("OH\n");
        return ;
    }
}

void receiveAck() {
    pthread_t p2;
    if(pthread_create(&p2,NULL,&rec,NULL) != 0) {
        printf("OH\n");
        exit(1);
    }
}


void alarmHandle(int sig) {
    msgFlg = IPC_NOWAIT;
}

int main() {
    signal(SIGALRM, alarmHandle);
    int Tframe = 1;
    int Tprop = 2, sn = 0;
   struct msgbuf buf;
   //int msqid;
   int len;
   key_t key;
   
    if ((key = ftok("may", 69)) == -1) {
        perror("ftok");
        exit(1);
    }
   
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }


    int bw, Lframe, Lchannel;
    // printf("Enter BW: ");
    // scanf("%d", &bw);

    // printf("Enter Lframe: ");
    // scanf("%d", &Lframe);

    // printf("Enter Lchannel: ");
    // scanf("%d", &Lchannel);

    //sendConfig(qid, bw, Lframe, Lchannel);
    int n;
    printf("\nEnter frame time (Tframe): ");
    scanf("%d", &Tframe);
    printf("Enter propagation delay (Tprop): ");
    scanf("%d", &Tprop);

    int done = 0;

    //buf.seqNum = (sn+1)%2;
    buf.mtype = 1;
    buf.mtext[0] = (char)Tprop;
    len = 1;
    if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
        perror("msgsnd");
    else
        printf("Time sent to channel\nStart sending data to receiver via the channel...\n\n");
    fflush(stdin);
    memset(&buf, 0, sizeof buf);
    getchar();
    printf("MESSAGE: ");


    FILE *fp;
    char *line = NULL;
    size_t lenn = 0;
    ssize_t read;
    fp = fopen("test", "r");
    if(fp == NULL) {
        printf("Cannot read file...\n");
        exit(1);
    }


    // while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
    while(read = getline(&line, &lenn, fp) != -1) {
        strcpy(buf.mtext, line);
        while(notSent) {
            if(strcmp(buf.mtext, "end\n") == 0) {
                done = 1;
                break;
            }
            buf.seqNum = (sn+1)%2;
            buf.mtype = 1;
            len = strlen(buf.mtext);
            /* remove newline at end, if it exists */
            if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
            //startTimer();
            alarm(6);
            sleep(Tframe);
            if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
                perror("msgsnd");
            else
                printf("Sent to messageQ\n");



            // RECEIVE ACK FROM CHANNEL
            //bzero(buf, sizeof(buf));
            struct msgbuf buff;
            if (msgrcv(msqid, &buff, sizeof(buff.mtext), 4, msgFlg) == -1) {
                // perror("msgrcv");
                // exit(1);
                msgFlg = 0;
                printf("Timer OUT. Sending again...\n");
                continue;
            }
            alarm(1000);
            //notSent = 0;
            printf("ACK received\n\nMESSAGE: ");
            break;
        }
        if(done) break;
    }
    

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
    }
    printf("msgQ removed\n");
   return 0;
}