#include <bits/stdc++.h>
#include <stdio.h>
#include <pcap.h>
using namespace std;
int hexadecimalToDecimal(string hexVal) ;
void verifychecksum()
{
	ifstream f("checksum.txt");
	int ans=0;
	for(int i=0;i<10;i++)
	{
		string x1,x2;
		f>>x1>>x2;
		
		//cout<<hexadecimalToDecimal(x)<<" ";
		ans+=hexadecimalToDecimal(x1+x2);
		bitset<17> bset(ans);
		if(bset[16]==1)
		{
			bitset<16> bset2;
			for(int i=0;i<16;i++)
				bset2[i]=bset[i];
			int temp=bset2.to_ulong();
			temp+=1;
			ans=temp;
		}
	}
	

	cout<<"Value of sum of all IP Header bytes  : ";
	bitset<16> bset3(ans);
	for(int i=15;i>=0;i--)
	{
		if(bset3[i]==0)
			bset3[i]=1;
		else
			bset3[i]=0;
	}
	for(int i=15;i>=0;i--)
		{
			cout<<bset3[i];
			if(i%4==0)
				cout<<" ";
		}
}
int hexadecimalToDecimal(string hexVal) 
{    
    int len = hexVal.length(); 
    int base = 1; 
    int dec_val = 0; 
    for (int i=len-1; i>=0; i--) 
    {    
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
            base = base * 16; 
        } 
        else if (hexVal[i]>='a' && hexVal[i]<='f') 
        { 
            dec_val += (hexVal[i] - 87)*base; 
            base = base*16; 
        } 
    } 
    return dec_val; 
} 
string converttohexa(char c)
{
	string temp;
	bitset<8> bset(c);
	bitset<4> bset1;
	bitset<4> bset2;
	for(int i=0;i<4;i++)
	{
		bset1[i]=bset[i];
	}
	for(int i=0;i<4;i++)
	{
		bset2[i]=bset[i+4];
	}
	/********/
	if(bset2==0)
		temp+="0";
	else if(bset2==1)
		temp+="1";
	else if(bset2==2)
		temp+="2";
	else if(bset2==3)
		temp+="3";
	else if(bset2==4)
		temp+="4";
	else if(bset2==5)
		temp+="5";
	else if(bset2==6)
		temp+="6";
	else if(bset2==7)
		temp+="7";
	else if(bset2==8)
		temp+="8";
	else if(bset2==9)
		temp+="9";
	else if(bset2==10)
		temp+="a";
	else if(bset2==11)
		temp+="b";
	else if(bset2==12)
		temp+="c";
	else if(bset2==13)
		temp+="d";
	else if(bset2==14)
		temp+="e";
	else if(bset2==15)
		temp+="f";	


	if(bset1==0)
		temp+="0";
	else if(bset1==1)
		temp+="1";
	else if(bset1==2)
		temp+="2";
	else if(bset1==3)
		temp+="3";
	else if(bset1==4)
		temp+="4";
	else if(bset1==5)
		temp+="5";
	else if(bset1==6)
		temp+="6";
	else if(bset1==7)
		temp+="7";
	else if(bset1==8)
		temp+="8";
	else if(bset1==9)
		temp+="9";
	else if(bset1==10)
		temp+="a";
	else if(bset1==11)
		temp+="b";
	else if(bset1==12)
		temp+="c";
	else if(bset1==13)
		temp+="d";
	else if(bset1==14)
		temp+="e";
	else if(bset1==15)
		temp+="f";	
	return temp;
}
int main()
{
	int i=0;
	int offset=40;
	ifstream f("example4.pcap",ios::binary|ios::in);
	ofstream out("checksum.txt");
	char c;
	int count=1;
	while(f.get(c))
	{
		if(count<=offset)
			{
				count++;
				continue;
			}
		if(count>=15+offset&&count<=34+offset)	
		out<<converttohexa(c)<<" ";
		// printf("%02x",(u_char)c);
		// printf(" ");

		count++;
	}
	out.close();
	cout<<"Verify File Now ?(Y/n) ";
		string temp;
		cin>>temp;
		if(temp=="Y"||temp=="y")
		{
			verifychecksum();
		}	
}