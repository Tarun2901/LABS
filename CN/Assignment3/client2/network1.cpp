#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;
#define PORT "3000"

void func(int new_s,int s){
	
	char message[1024];
	while(1){
		bzero(message, 1024);
	   	read(new_s, message, sizeof(message));
		if(strncmp(message,"quit",4) == 0){
			cout<<"Closing connection at Server side\n";
			break;
		}
		cout << "Message received from client: " << message << endl;
		bzero(message, 1024);
	    cout <<"Enter a message to send: ";
	    fgets(message,1024,stdin);

	    int bytes_sent = send(new_s ,(void *)message, 1024,0);
	}
}

int main(){
	struct addrinfo hints;
	struct addrinfo* servinfo;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0; //find number for IPV4
	
	int status = getaddrinfo(NULL,PORT, &hints, &servinfo);
	if(status != 0){
		std::cout<<"Couldn't load the server\n";
		exit(1);
	}

	int s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	int bindstatus = bind(s,servinfo->ai_addr,servinfo->ai_addrlen);
	
	int l_listen = listen(s,5);
	
	
	struct sockaddr_storage client;
	socklen_t client_size = sizeof (client);

		cout<<"Waiting for a new connection...\n";
		int new_s = accept(s, (struct sockaddr *)&client, &client_size);
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
		func(new_s,s);
		
		close(new_s);
	
	freeaddrinfo(servinfo);
}
