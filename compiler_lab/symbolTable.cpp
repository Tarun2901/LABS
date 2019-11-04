#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define SIZE 100
static int mAdd;

int hashFunc(string key){
	int sum=0;
	for(int i=0;i<key.size();i++){
		sum += (i+1)*key[i];
	}
	sum=sum%SIZE;
	return sum;
}

class Node{
public:
	string identifier;
	int memAdd;
	Node* next;

	Node(string key,int add){
		identifier=key; memAdd=add;
		next=NULL;
	}
};

void insertNode(Node* temp,string key,int mAdd){
	while(temp->next){
		temp=temp->next;
	}
	temp->next=new Node(key,mAdd);
}	

class SymbolTable{
	Node* Arr[SIZE];
public:
	SymbolTable(){
		for(int i=0;i<SIZE;i++){
			Arr[i]=NULL;
		}
	}
	
	void AddEntry(string key){
		int index=hashFunc(key);
		Node* temp=Arr[index];
		if(!temp){
			Arr[index] = new Node(key,++mAdd);
		}
		else{
			insertNode(temp,key,++mAdd);
		}
	}

	int search(string key){
		int index=hashFunc(key);
		Node* temp = Arr[index];

		while(temp && temp->identifier!=key){
			temp=temp->next;
		}
		if(temp){
			return temp->memAdd;
		}
		else{
			return -1;
		}
	}
};

int main(){
	mAdd=0;
	SymbolTable myST;

	vector<string> A;
	A.push_back("ab");
	A.push_back("ba");
	A.push_back("aaa");

	for(string x:A){
		myST.AddEntry(x);
	}
	for(string x:A){
		cout<<x<<": "<<myST.search(x)<<endl;
	}
}
