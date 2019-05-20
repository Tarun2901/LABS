#include <iostream>
#include <graphics.h>

#define LEFT 0x1
#define BOTTOM 0x2
#define RIGHT 0x4
#define TOP 0x8

using namespace std;

struct point
{
    float x,y;
};

float xmin,ymin,xmax,ymax;

int code(point a)
{
    int reg=0x0;

    if(a.x<xmin)
        reg=reg|LEFT;
    else if(a.x>xmax)
        reg=reg|RIGHT;
    if(a.y<ymin)
        reg=reg|BOTTOM;
    else if(a.y>ymax)
        reg=reg|TOP;
    return reg;
}

void clipping(point ini, point fin, int X, int Y){
    setcolor(RED);
    float m=(fin.y-ini.y)/(fin.x-ini.x);
    line(xmin+X,Y-ymin,X+xmax,Y-ymin);
    line(xmax+X,Y-ymin,X+xmax,Y-ymax);
    line(X+xmax,Y-ymax,X+xmin,Y-ymax);
    line(X+xmin,Y-ymax,X+xmin,Y-ymin);
    setcolor(WHITE);
    while (1) {
        int r1=code(ini);
        int r2=code(fin);
        if ((r1&r2)!=0) {
            break;
        }
        if((r1|r2)==0) {    //visible
            line(ini.x+X,Y-ini.y,X+fin.x,Y-fin.y);
            break;
        }
        //partially
        if(r1==0) {     //ensuring r1 always has non centre coordinate
            int temp=r1;
            r1=r2;
            r2=temp;
            point t=ini;
            ini=fin;
            fin=t;
        }
        if(r1&LEFT) {
            float ynew=m*(xmin-ini.x)+ini.y;
            point t = ini;
            ini.y=ynew;
            ini.x=xmin;
            setcolor(YELLOW);
            line(X+t.x,Y-t.y,X+ini.x,Y-ini.y);
            setcolor(WHITE);
        }
        else if(r1&RIGHT) {
            float ynew=m*(xmax-ini.x)+ini.y;
            point t = ini;
            ini.y=ynew;
            ini.x=xmax;
            setcolor(YELLOW);
            line(X+t.x,Y-t.y,X+ini.x,Y-ini.y);
            setcolor(WHITE);
        }
        else  if(r1&BOTTOM) {
            float xnew=(1/m)*(ymin-ini.y)+ini.x;
            point t = ini;
            ini.y=ymin;
            ini.x=xnew;
            setcolor(YELLOW);
            line(X+t.x,Y-t.y,X+ini.x,Y-ini.y);
            setcolor(WHITE);
        }
         else  if(r1&TOP) {
            float xnew=(1/m)*(ymax-ini.y)+ini.x;
            point t = ini;
            ini.y=ymax;
            ini.x=xnew;
            setcolor(YELLOW);
            line(X+t.x,Y-t.y,X+ini.x,Y-ini.y);
            setcolor(WHITE);
        }
    }
}

int main()
{
    cout << "Enter coordinates of rectangular window xmin ymin xmax ymax : ";
    cin >> xmin >> ymin >> xmax >> ymax;
    cout << "Enter the end points initial.x initial.y final.x final.y \n: ";
    point ini,fin;
    cin >> ini.x >> ini.y >> fin.x >> fin.y;

    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    int X = getmaxx()/2;
    int Y = getmaxy()/2;
    clipping(ini, fin, X, Y);
    char c;
    cin>>c;
    return 0;
}

