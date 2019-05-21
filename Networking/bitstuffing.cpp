#include<iostream>
#include<string>

using namespace std;
int main()
{
   int a[20],b[30];
   int i,j,k,count,n;

   cout << "Enter frame size n : ";
   cin >> n;
   cout << "Enter the frame (Stream of bits) : ";

   for(i=0; i<n; i++)
       cin >> a[i];

   i=0;
   count=1;
   j=0;
   while(i<n)
   {
       if(a[i]==1)
       {
           b[j]=a[i];
           for(k=i+1; a[k]==1 && k<n && count<5; k++)
           {
               j++;
               b[j]=a[k];
               count++;
               if(count==5)
               {
                   j++;
                   b[j]=0;
               }
               i=k;
           }
       }
       else
       {
           b[j]=a[i];
       }
       i++;
       j++;
   }
   cout << "After Bit Stuffing :";
   for(i=0; i<j; i++)
       cout << b[i];

   return 0;
}
