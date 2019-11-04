#include <cstdio>
#include <cstdlib>
using namespace std;
int main () 
{
   char i(0),*pEnd,byte[3] = {0}; 
   unsigned char suc(0),pole[50];
   FILE*read=fopen("packet.txt","r");
   while ((fscanf(read,"%c%c",&byte[0],&byte[1]))!=EOF) { 
       pole[i]=static_cast<unsigned char>(strtol(byte,&pEnd,16));
       suc+=(~pole[i++]+1); 
       // Not knowing your input file I am going to break
       // after reading 20
       if ( i == 20 )
         break;
   }
 
   for (i=0;i<20;i++)
      printf("%02x",pole[i]);
   printf("\n checksum: %02X\n",suc); 

   fclose(read);   
}