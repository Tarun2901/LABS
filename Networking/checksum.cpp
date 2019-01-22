#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;

int main(){
	ifstream f("/home/nishant/Desktop/lab1.pcap",ios::binary|ios::in) ;
	char c ;	
	int offset=0 ;
	u_char c1 , c2 ;
	printf("Destination Mac Address: ");
	while(f.get(c)){
		++offset ;
		if(offset<=40){
			continue ;
		}
		
		printf("%02x",(u_char)c);
		printf(" ");
		
		if(offset > 45){
			break ;
		}
	}
	printf("\n");
	printf("Source Mac Address: ");
	while(f.get(c)){
		++offset ;
		printf("%02x",(u_char)c);
		printf(" ");
		
		if(offset > 51){
			break ;
		}

	}
	while(f.get(c)){
		++offset ;
		if(offset==65){
			c1=c ;
		}
		if(offset==66){
			c2=c ;
		}
		if (offset>70){
			break ;
		}
	}
	printf("\n");
	printf("CheckSum : %02x%02x\n",c1,c2) ;
	f.close() ;
	
}