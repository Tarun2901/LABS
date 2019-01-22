#include<iostream>
#include<fstream>

using namespace std;
int main()
{
	ifstream file;
	int i;
	size_t pos;
	string line, search = "inet";
	system("ifconfig wlp1s0 1> log");
	file.open("log");
	while(getline(file, line))
	{
		pos = line.find(search);
		if(pos != string::npos)
		{
			cout<<"IPv4 Address: ";
			for(i = pos + search.size() + 1; line[i] != ' '; i++)
				cout<<line[i];
			cout<<"\n";
			search = " netmask ";
			i += search.size() + 1;
			cout<<"Netmask: ";
			for(; line[i] != ' '; i++)
				cout<<line[i];
			cout<<"\n";
			search = "inet6";
			getline(file, line);
			pos = line.find(search);
			if(pos != string::npos)
			{
				cout<<"IPv6 Address: ";
				for(i = pos + search.size() + 1; line[i] != ' '; i++)
					cout<<line[i];
				cout<<"\n";
			}
			search = "ether";
			getline(file, line);
			pos = line.find(search);
			if(pos != string::npos)
			{
				cout<<"mac Address: ";
				for(i = pos + search.size() + 1; line[i] != ' '; i++)
					cout<<line[i];
				cout<<"\n";
			}
			break;
		}
	}
	file.close();
	search = "default via";
	file.close();
	system("ip route show 1> log");
	file.open("log");
	while(getline(file, line))
	{
		pos = line.find(search);
		if(pos != string::npos)
		{
			cout<<"Default Gateway: ";
			for(i = pos + search.size() + 1; line[i] != ' '; i++)
				cout<<line[i];
			cout<<"\n";		
			break;
		}
	}
	return 0;
}