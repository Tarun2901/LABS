#include<iostream>
#include<fstream>
#include<stdio.h>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/if_ether.h>
using namespace std;


// First forty bytes are File Header


int main(){
	ifstream f("c2.pcap", ios::binary | ios::in);
	char c;
	int bits[1000];
	
	// Extract the checksum from .pcap file
	int count = 1;
	while (f.get(c))
	{
		// File header contains 40 bytes
		if(count <=40){
			count++; continue;
		}
		
		if(count == 41){
			cout<<"Destination MAC Address:\t";
			printf("%02X:",(unsigned char)c);
			count++;	
			while(count<=46){
				f.get(c);
				printf("%02X:",(unsigned char)c);
				count++;
			}
			cout << endl;
			continue;
		}

		if(count == 47){
			cout<<"Source MAC Address:\t";
			printf("%02X:",(unsigned char)c);
			count++;	
			while(count<=52){
				f.get(c);
				printf("%02X:",(unsigned char)c);
				count++;
			}
			cout << endl;
			continue;
		}


		// if(count == 65 || count == 66){
		// 	if(count == 65){
		// 		cout<<"CheckSum is:\t";
		// 	}
		// 	printf("%02X",(unsigned char)c);
		// 	if(count == 66)
		// 		cout << endl;
  //      	}
       	if(count == 67){
			cout<<"Source IP Address:\t";
			printf("%02X:",(unsigned char)c);
			count++;	
			while(count<=70){
				f.get(c);
				printf("%02X:",(unsigned char)c);
				count++;
			}
			cout << endl;
			continue;
		}
		if(count == 71){
			cout<<"Destination IP Address:\t";
			printf("%02X:",(unsigned char)c);
			count++;	
			while(count<=74){
				f.get(c);
				printf("%02X:",(unsigned char)c);
				count++;
			}
			cout << endl;
			continue;
		}
       	count++;
    }
}	 	

