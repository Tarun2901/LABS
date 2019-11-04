//od --endian='big' -x c2.pcap
#include<iostream>
#include<bitset>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

int main()
{
	//system("od --endian='big' -An -j54 -x -N20 -w40 c2.pcap 1> packet.txt");
	// An  :No offset info
	// j40 :set offset
	// x   :Hexadecimal
	ifstream myfile;
    myfile.open("packet.txt");

    //vector<bitset<17> > numbers;
    bitset<17> sum = 0;
    int checksum = 0;
	int count = 0;
    while(++count<=10){
			

			string temp1,temp2;
	    	myfile >> temp1;
	    	
	    	int tempValue1,tempValue2;
	    	istringstream ost(temp1);
			ost >> hex >> tempValue1;
			
			int tempValue = tempValue1;

			sum = sum.to_ulong() + tempValue;
			if(sum[16] == 1){
				sum.reset(16);
				sum = sum.to_ulong() + 1;
			}
			//cout << sum.to_ulong() << endl;
			//cout << endl << sum << "\t" <<sum.to_ulong() <<endl;
		//cout << addr << endl;
		//numbers.push_back(addr);
	}

	sum[16] = 1;
    sum = sum.flip();
    cout << hex << sum.to_ulong() << endl;

    //bitset<17> checksum = numbers[5];
	//numbers.erase(numbers.begin()+5);


    //cout << endl << checksum <<endl << numbers[4] << endl << numbers[5];

	// bitset<17> sum = 0;
	// cout << sum << endl;
 //    //cout << numbers[0] << endl;
 //    for(int i=0;i<numbers.size();i++){
 //    	bitset<17> temp(sum.to_ulong() + numbers[i].to_ulong());
 //    		if(temp[16] == 1){
 //    			//cout << i << "\n" << numbers[i] << endl << sum << endl;
 //    			//cout <<endl<< temp << endl;
	//     		temp.reset(16);
	//     		temp = temp.to_ulong() + 1; 
	//     		//cout << temp << endl;
	//     	}
 //    	sum = temp;	
 //    	//cout << sum << endl << endl;
 //    }

 //    //sum = sum.to_ulong() + checksum.to_ulong();
 //   	cout << sum << endl;
 //   //	sum = sum.flip();
 //   	//sum.reset(1)
 //   	//cout << endl << sum << endl << checksum;
}
