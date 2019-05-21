#include<iostream>
using namespace std;

int main()
{
int i,j,k,data[100],n;



cout << "Enter no. of bits :\n";
cin >> n;
cout << "Enter data to be sent :\n";
for(i=0;i<n;i++)
scanf("%d",&data[i]);


for(i=0;i<n;i++)
{
if(data[i]==0)
 if(data[i+1]==1)
   if(data[i+2]==1)
     if(data[i+3]==1)
       if(data[i+4]==1)
         if(data[i+5]==1)
           if(data[i+6]==1)
             if(data[i+7]==0)
             {
               i=i+8;
               for(j=i+8;j>=i;j--)
               {
                   data[j+8]=data[j];
                   n++;
               }
               for(k=0;k<8;k++)
               {
                   if(k==0||k==7)
                   data[i]=0;
                   else
                   data[i]=1;
                   i++;
               }

             }
}

cout << "The byte stuffed array is\n";
for(i=0;i<n-1;i++)
cout << data[i];

return 0;

}
