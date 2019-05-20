#include<iostream>
#include<graphics.h>
#include<cmath>
using namespace std;

void makeQuadrant(int x,int y,int col)
{
    putpixel(320+x,240-y,col);
    putpixel(320+x,240+y,col);
    putpixel(320-x,240-y,col);
    putpixel(320-x,240+y,col);
}

void bresenellipse(int a,int b,int col)
{
    int d=a*a+2*b*b-2*a*a*b;
    int x=0,y=b;
    float xx=a*a/sqrt(a*a+b*b),yy=b*b/sqrt(a*a+b*b);
    while(x<=xx&&y>=yy){
        if(d<=0){
            x++;
            d+=2*b*b*(2*x+3);
        }
        else if(d>0){
            y--;
            x++;
            d+=4*b*b*x+6*b*b-4*a*a*y+4*a*a;
        }
        makeQuadrant(x,y,col);
    }
    while(x<=a&&y>=0){
        if(d<=0){
            y--;
            d+=2*a*a*(2*y-3);
        }
        else if(d>0){
            y--;
            x++;
            d-=4*b*b*x+4*b*b-4*a*a*y+6*a*a;
        }
        makeQuadrant(x,y,col);
    }
}

int main()
{
    int a,b;
    cout<<"Enter a b : \n";
    cin>>a>>b;
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    bresenellipse(a,b,WHITE);
    getch();
    closegraph();
    return 0;
}
