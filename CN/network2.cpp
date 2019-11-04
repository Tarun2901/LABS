#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
using namespace std;
#define PORT 3000


int main(){
	struct addrinfo hints;
	struct addrinfo* servinfo;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; 
	//hints.ai_protocol = 0; //find number for IPV4
	
	int status = getaddrinfo(NULL, "3000", &hints, &servinfo);
	if(status != 0){
		std::cout<<"Couldn't load the server\n";
		exit(1);
	}


	int s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	int connect_status = connect(s,servinfo->ai_addr,servinfo->ai_addrlen);
	if(connect_status != 0){
		cout <<"Connection with server failed\n";
		exit(1);
	}

	cout <<"Connected to server\n";
	
	char message[1024];
	while(1){
	   bzero(message, 1024);
	   cout <<"Enter a message to send: ";
	   fgets(message,1024,stdin);

	   int bytes_sent = send(s ,(void *)message, 1024,0);
	   if(strncmp(message,"quit",4) == 0){
			cout<<"Closing connection at Client side\n";
			exit (0);
		}

	   bzero(message,1024);
	   read(s, message, sizeof(message));
	   cout<<"Message received is: "<< message << endl;
	}
		
	freeaddrinfo(servinfo);
}