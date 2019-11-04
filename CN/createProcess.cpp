#include <unistd.h>
#include<iostream>
using namespace std;

int main()
{
    int childId = fork(); // -1 if failure, 0 if entered child process or a +ve process id
	int superParentId = getppid();
    int currentProces = getpid();
    
    cout << "Parent Id:" <<superParentId << "\nCurrent Process:" << currentProces << endl;
    int x;
    cin >> x; 
}

