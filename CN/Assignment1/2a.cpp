#include<iostream>
#include<fstream>
using namespace std;

void print(string data,string word)
{
	int pos = data.find(word);
	string target = data.substr(pos,word.length());
	cout << target << ":\t\t";
	char ch ='a';
	int i= pos + target.length()+1;
	while(ch != ' '){
		ch = data[i++];
		cout << ch;
	}	
	cout << endl;
}

void readData(ifstream&	infile, string& data){
	while(!infile.eof()){
		string temp;
		infile >> temp;
		
		data += temp + " ";
	}
}

int main(){
	system("ifconfig -a wlp2s0 1> tempout1"); 
	system("systemd-resolve --status 1> tempout2"); // DNS Domain and DNS Server
	system("ip route 1> tempout3"); // for gateways
	
	string data;
	
	ifstream infile;
	infile.open("tempout1");
	readData(infile,data);
	infile.close();

	data += "\n";
	infile.open("tempout2");
	readData(infile,data);
	infile.close();

	data += "\n";
	infile.open("tempout3");
	readData(infile,data);
	

    cout << "Details Extracted are:\n";
	print(data,"inet");
	print(data,"inet6");
	print(data,"ether");
	print(data,"broadcast");
	print(data,"DNS Domain:");
	print(data,"DNS Servers:");
	print(data,"netmask");
	print(data,"default via");

}
