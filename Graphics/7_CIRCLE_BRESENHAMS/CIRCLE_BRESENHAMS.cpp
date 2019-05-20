#include<iostream>
#include<graphics.h>
#include<math.h>
#define PI 3.148
using namespace std;

/*
void quadrantBanao(int x,int y,int col)
{
    putpixel(320+x,240-y,col);
    putpixel(320+x,240+y,col);
    putpixel(320-x,240-y,col);
    putpixel(320-x,240+y,col);
}
*/
void point(int x, int y, int ox, int oy, int color){
    if(ox+x>=0 && oy-y>=0 && ox+x<getmaxx() && oy-y<getmaxy())
        putpixel(ox+x,oy-y,color);
    else
        cout<<ox+x<<","<<oy-y<<" : Pixel out of bound\n";//display a point x,y with respect to origin at ox,oy
}

void circlePoint(int x, int y, int ox, int oy, int color){
    point(x,-1*y,ox,oy,color);
    point(-1*x,-1*y,ox,oy,color);
    point(x,y,ox,oy,color);
    point(-1*x,y,ox,oy,color);
}

void drawCircle(int cx, int cy,int r,int col)
{
    int d=2*(1-r);
    int x=0,y=r;
    while(x>=0&&y>=0){
        if(d<0){
            x++;
            d+=2*x+3;
        }
        else if(d>0){
            y--;
            d+=3-2*y;
        }
        else{
            x++;
            y--;
            d+=2*(x-y)+6;
        }
        circlePoint(x,y,cx,cy,col);
    }
}

int main()
{
    int gd = DETECT, gn,x,y,r;
    initgraph(&gd,&gn,NULL);
    int X = getmaxx();
    int Y = getmaxy();
    setcolor(WHITE);
    line(0,Y/2,X,Y/2);// x axis
    line(X/2,0,X/2,Y);// y axis
    setcolor(1);
    cout<<"Enter x y radius : \n";
    cin>>x>>y>>r;
    drawCircle(X/2+x,Y/2-y,r,WHITE);
    //drawCircle(X/2,Y/2,X/8,4);
    char c;
    cin>>c;
    closegraph();
}
