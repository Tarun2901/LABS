#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>

using namespace std;

int main()
{
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, NULL);
    //errorcode = graphresult();

    /*
    if (errorcode != grOk)
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);
    }
    */
    int wind[6][2]= {{30,150},{25,60},{80,70},{30,50},{100,40},{10,10}};
    int point[2][2]= {{10,120},{80,-20}};
    int inters[6][2];
    int i;

    int edge[6][2];
    for(i=0; i<5; i++)
    {
        edge[i][0]=wind[i+1][0]-wind[i][0];
        edge[i][1]=wind[i+1][1]-wind[i][1];
    }
    edge[5][0]=wind[0][0]-wind[5][0];
    edge[5][1]=wind[0][1]-wind[5][1];

    int nor[6][2];
    for( i=0; i<6; i++)
    {
        nor[i][0]=-edge[i][1];
        nor[i][1]=edge[i][0];

    }
    float num[6],den[6],t[6];

    for( i=0; i<6; i++)
    {

        float numx=(point[0][0]-wind[i][0])*(nor[i][0]);
        float numy=(point[0][1]-wind[i][1])*(nor[i][1]);
        num[i]=numx+numy;
        float denx=((nor[i][0])*(point[1][0]-point[0][0]));
        float deny=((nor[i][1])*(point[1][1]-point[0][1]));
        den[i]=-(denx+deny);
        t[i]=num[i]/den[i];
    }

    setcolor(RED);
    for(i=0; i<5; i++)
    {
        line(360+wind[i][0],240-wind[i][1],360+wind[i+1][0],240-wind[i+1][1]);
    }
    line(360+wind[5][0],240-wind[5][1],360+wind[0][0],240-wind[0][1]);

    for(i=0; i<6; i++)
    {
        inters[i][0]=point[0][0]+(point[1][0]-point[0][0])*t[i];
        inters[i][1]=point[0][1]+(point[1][1]-point[0][1])*t[i];
    }

    setcolor(YELLOW);
    line(360+inters[1][0],240-inters[1][1],360+inters[2][0],240-inters[2][1]);
    line(360+inters[3][0],240-inters[3][1],360+inters[4][0],240-inters[4][1]);
    line(360+inters[5][0],240-inters[5][1],360+inters[0][0],240-inters[0][1]);

    setcolor(CYAN);
    line(360+point[0][0],240-point[0][1],360+inters[5][0],240-inters[5][1]);
    line(360+inters[0][0],240-inters[0][1],360+inters[1][0],240-inters[1][1]);
    line(360+inters[2][0],240-inters[2][1],360+inters[3][0],240-inters[3][1]);
    line(360+point[1][0],240-point[1][1],360+inters[4][0],240-inters[4][1]);


    getch();
    closegraph();
    return 0;
}
