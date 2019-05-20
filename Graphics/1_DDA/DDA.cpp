#include<iostream>
#include<graphics.h>
#include<math.h>

using namespace std;

void put_pixel(int x, int y, int col)
{
  putpixel(x+320, 240-y, col);
}

int round(float x)
{
  double rem = fmod((double)x,1.0);
  if(x<0.5)
    return (floor((double)x));
  else
    return (ceil((double)x));
}


void dda(int x1, int y1, int x2, int y2)
{
  int xa,ya,xb,yb;
  if(x1<x2)
  {
    xa=x1;ya=y1;
    xb=x2;yb=y2;
  }
  else
  {
    xa=x2;ya=y2;
    xb=x1;yb=y1;
  }

  int dx,dy;
  dx=xb-xa;
  dy=yb-ya;
  int steps;
  float x=xa,y=ya;
  if (abs(dx)>abs(dy))
    steps = abs(dx);
  else
    steps = abs(dy);
  float xinc,yinc;
  xinc = 1.0*dx/steps;
  yinc = 1.0*dy/steps;
  put_pixel(xa,ya,RED);
  while(x<xb)
  {
    x+=xinc;
    y+=yinc;
    put_pixel(round(x),round(y),RED);
  }
}

int main()
{
  int x1,y1,x2,y2;
  int gd = DETECT, gm;
  initgraph(&gd,&gm,NULL);
  setcolor(WHITE);
  line(320,0,320,480);
  setcolor(WHITE);
  line(0,240,640,240);
  cout<<"Enter x1,y1 : ";
  cin>>x1>>y1;
  cout<<"Enter x2,y2 : ";
  cin>>x2>>y2;
  setcolor(RED);
  dda(x1,y1,x2,y2);
  getch();
  closegraph();
}


