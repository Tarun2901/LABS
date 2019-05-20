#include<iostream>
#include<bits/stdc++.h>
#include<graphics.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
float ob[4][8]={
0 ,40,40,0 ,0 ,40,40,0,
0 ,0 ,40,40,0 ,0 ,40,40,
0 ,0 ,0 ,0 ,40,40,40,40,
1,1,1,1,1,1,1,1
};
float t,pi=3.14;
float ob1[4][8],ob2[4][8];

float roty[4][4]=
    {cos(pi/180),0,sin(pi/180),0,
    0,1,0,0,
    -sin(pi/180),0,cos(pi/180),0,
    0,0,0,1
    };
    float rotx[4][4]=
    {1 ,0,0,0,
    0,cos(pi/180),-sin(pi/180),0,
    0,sin(pi/180),cos(pi/180),0,
    0,0,0,1
    };
    float rotz[4][4]=
    {cos(pi/180),-sin(pi/180),0,0,
     sin(pi/180),cos(pi/180),0,0,
     0,0,1,0,
     0,0,0,1};
     float isometric[4][4]={0.7071,0,-0.7071,0,-0.40825,0.8165,-0.40825,0,0.7071,0.40825,0.8165,0,0,0,0,1};

     //matmul(isometric,ob1);
void matmul(float mat1[4][4],float mat2[4][8])
{
    float res[4][8];
    int i,j,k;
    for(i=0;i<4;i++)
    {
        for(j=0;j<8;j++)
        {
            res[i][j]=0;
            for(k=0;k<4;k++)
            {
                res[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
    for(int i=0;i<4;i++){
            for(int j=0;j<8;j++)
                mat2[i][j]=res[i][j];
        }
}

void diview(float ob[4][8])
{
     int i=0;
    for(i=0;i<4;i++)
        line(219+ob[0][i%4],300-ob[1][i%4],219+ob[0][(i+1)%4],300-ob[1][(i+1)%4]);
    for(i=4;i<8;i++)
         line(219+ob[0][i%4+4],300-ob[1][i%4+4],219+ob[0][(i+1)%4+4],300-ob[1][(i+1)%4+4]);

    for(i=0;i<4;i++)
        line(219+ob[0][(i%8)],300-ob[1][i%8],219+ob[0][(i+4)%8],300-ob[1][(i+4)%8]);
}
//float dimetric[4][4];
void rot(float ob[4][8],float ob1[4][8],float ob2[4][8],float dimetric[4][4])
{
    float t;
     float obnew[4][8];
    int i,j,k;
    matmul(isometric,ob1);
    matmul(dimetric,ob2);
    for(t=0;t<=10;t+=0.01)
    {

    matmul(roty,ob);
    matmul(rotx,ob1);
    matmul(rotx,ob2);
        setcolor(WHITE);
        diview(ob2);
        delay(20);
        cleardevice();
    }

}
int main()
{
    int gdrive=DETECT,gmode;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<8;j++)
        {
            ob1[i][j]=ob2[i][j]=ob[i][j];
        }
    }
    float th1,th2,k;

    cout<<"enter k";
    cin>>k;
    th1=acos(sqrt(k*k/2)),th2=acos(sqrt(2/(k*k+2)));
    float dimetric[4][4]={cos(th1),0,-sin(th1),0,-sin(th1)*sin(th2),cos (th2),-sin(th2)*cos(th1),0,cos(th2)*sin(th1),sin(th2),cos(th2)*cos
    (th1),0,0,0,0,1};
    initgraph(&gdrive,&gmode,NULL);
    rot(ob,ob1,ob2,dimetric);
    getch();
    return 0;
}
