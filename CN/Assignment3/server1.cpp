// -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include<iostream>
#include <pthread.h>

using namespace std;
#define PORT "3000"
#define MAX_LISTEN 10

void closing_print(){
	cout<<"****************************************\n";
	cout<<"****************************************\n";
	cout<<"****************************************\n\n\n";

}

void func(int new_s,int s){
	
	char message[1024];
	while(1){
		bzero(message, 1024);
	   	read(new_s, message, sizeof(message));
		if(strncmp(message,"quit",4) == 0){
			cout<<"Closing connection at Server side\nClosing initiated by client\n";
			closing_print();
			break;
		}
		cout << "Message received from client: " << message << endl;
		bzero(message, 1024);
	    cout <<"Enter a message to send: ";
	    fgets(message,1024,stdin);

	 	int bytes_sent = send(new_s ,(void *)message, 1024,0);
	 	if(strncmp(message,"quit",4) == 0){
			cout<<"Closing connection at Server side\nClosing initiated by server\n";
			closing_print();
			break;
		}
		
	}
}

class new_socket{
public:
	int new_s;
	int s;
};

void *func_thread(void* args){
	new_socket *x = (new_socket*)args;
	int new_s = x->new_s;
	int s = x->s;
	free(x);
	func(new_s,s);
	return NULL;
}


void sigchld_handler(int s)
{
	int saved_errno = errno;
	while(waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

int main(){
	struct addrinfo hints;
	struct addrinfo* servinfo,*p;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 	
	int sockfd;
	int yes=1;
	struct sigaction sa;
	socklen_t sin_size;

	
	int status = getaddrinfo(NULL,PORT, &hints, &servinfo);
	if(status != 0){
		std::cout<<"Couldn't load the server\n";
		exit(1);
	}
	
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
			sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);
	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
	
	int l_listen = listen(sockfd,MAX_LISTEN);
	if(l_listen == -1){
		cout<<"Listen failed\n";
		exit(1);
	}
	/* Killing any unused ports*/
	while(true){
		sa.sa_handler = sigchld_handler; // reap all dead processes
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		if (sigaction(SIGCHLD, &sa, NULL) == -1) {
			perror("sigaction");
			exit(1);
		}
			
		struct sockaddr_storage client;
		socklen_t client_size = sizeof (client);

			cout<<"Waiting for a new connection...\n";
			int new_s = accept(sockfd, (struct sockaddr *)&client, &client_size);
			if(new_s < 0){
				cout<<"Failed to accept at server";
				exit(1);
			}

			struct sockaddr_in peer;
			socklen_t peer_size = sizeof(peer);

			int peer_status =  getpeername(new_s, (struct sockaddr*)&peer, &peer_size);
			if(peer_status == -1){

			}
			char peer_ip4[INET_ADDRSTRLEN]; 
			inet_ntop(AF_INET, &(peer.sin_addr), peer_ip4, INET_ADDRSTRLEN);
			printf("The IPv4 address of client is: %s\n", peer_ip4);
			func(new_s,sockfd);

			//Threading try
			// pthread_t socket_thread;
			// new_socket *args = new new_socket();
			// args->new_s=new_s;
			// args->s=sockfd;
			
			// if(pthread_create(&socket_thread, NULL, func_thread, args)) 
	  //           free(args);
	        // sleep(100);
			
			close(new_s);
	}
	// pthread_join( socket_thread , NULL);
	wait(NULL);
}