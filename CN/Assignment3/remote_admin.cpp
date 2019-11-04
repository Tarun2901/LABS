#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using namespace std;

void printLiveHosts(){
  system("nmap -sP 192.168.1.100-104 > temp.txt");
  system("grep -o '[0-9]\\{1,3\\}\\.[0-9]\\{1,3\\}\\.[0-9]\\{1,3\\}\\.[0-9]\\{1,3\\}' temp.txt > hostsup.txt");
  // The hosts up are in the file hostsup.txt
  ifstream myfile("hostsup.txt");
  string line;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }
}

int main ()
{
  printLiveHosts();
  
}
