// to compile:  g++ 2_4.cpp -lpcap
#include <iostream>
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

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
int pktcnt=1;

int main() {
  pcap_t *descr;
  char errbuf[PCAP_ERRBUF_SIZE]; //error message

  // open capture file for offline processing
  descr = pcap_open_offline("c_tcp.pcap", errbuf);
  //cout << "descr:" <<descr << endl;
  
  // for(int i=0;i<PCAP_ERRBUF_SIZE;i++)
  // cout << errbuf[i];
	
  if (descr == NULL) {
      cout << "pcap_open_live() failed: " << errbuf << endl;
      return 1;
  }

  // start packet processing loop, just like live capture
  if (pcap_loop(descr, 0, packetHandler, NULL) < 0) {
      cout << "pcap_loop() failed: " << pcap_geterr(descr);
      return 1;
  }

  cout << "capture finished" << endl;

  return 0;
}

// const u_char packer points to the bytes of the packet
//(session handler,number of packets to live capture,structure,pointer to bytes)
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
  cout<<"Packet Number: "<<pktcnt<<"\n"; // print the packet number
  pktcnt++;
  const struct ether_header* ethernetHeader;
  const struct ip* ipHeader;
  const struct tcphdr* tcpHeader;

  u_char etherdhost [6];
  u_char ethershost [6];

  char sourceIp[INET_ADDRSTRLEN];
  char destIp[INET_ADDRSTRLEN];
  u_int sourcePort, destPort;
  u_char *data;//pcap function to get mac address
  int dataLength = 0;
  string dataStr = "";
  
  ethernetHeader = (struct ether_header*)packet;

  // Library function that extracts Source and Destination MAC Address
  char *p ,*q;
  p= ether_ntoa((struct ether_addr *) &ethernetHeader->ether_shost);
  cout<<"Source MAC address is : "<<p << endl;
  q= ether_ntoa((struct ether_addr *) &ethernetHeader->ether_dhost);
  cout<<"Destination MAC address is : "<<q<<"\n";

  // printf("Dest MAC: %s\n", ether_ntoa(&ethernetHeader->ether_dhost));
  // printf("Source MAC: %s\n", ether_ntoa(&ethernetHeader->ether_shost));

  if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
      ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
      inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIp, INET_ADDRSTRLEN);
      inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);
      switch(ipHeader->ip_p) {
    case IPPROTO_TCP:
      printf("Protocol Type : TCP\n");
      break;
    case IPPROTO_UDP:
      printf("Protocol Type : UDP\n");
      return;
    case IPPROTO_ICMP:
      printf("Protocol Type : ICMP\n");
      return;
    case IPPROTO_IP:
      printf("Protocol Type : IP\n");
      return;
    default:
      printf("Protocol Type : unknown\n");
      return;
  }
  

      if (ipHeader->ip_p == IPPROTO_TCP) {
          tcpHeader = (tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
          sourcePort = ntohs(tcpHeader->source);
          destPort = ntohs(tcpHeader->dest);
          data = (u_char*)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
          dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
          int checksum =  ipHeader -> ip_sum;
          int ip_id = ipHeader->ip_id;
          int version = ipHeader->ip_v;
          
          //print the results
          cout <<"Source Ip Address is :"<< sourceIp << "\nSource port is :" << sourcePort << "\nDestination Ip Address is :" << destIp << "\n Destination Port is:" << destPort << endl;
          cout << "Checksum is: " << checksum << endl;
          cout << "IP-id is: " << ip_id << endl;
          cout << "IP-Version is: " << version << endl;
          cout << "\n\n\n"; 
  
      }
  }
}
