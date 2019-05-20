#include<iostream>
#include <graphics.h>
#include<cmath>
//#include "makecircle.h"
using namespace std;

#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)

void putting_pixel(int a0, int a1, int c1, int x_pivot, int y_pivot, int angle)
{
    int x_shifted = a0 - x_pivot;
    int y_shifted = a1 - y_pivot;
    a0 = x_pivot + (x_shifted*COS(angle) - y_shifted*SIN(angle));
    a1 = y_pivot + (x_shifted*SIN(angle) + y_shifted*COS(angle));
    putpixel(a0, a1, c1);
}

void makeCircle(int x0, int y0, int r, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8, int x_pivot, int y_pivot, int angle)
{
    int R = r;
    int x = 0, y= R, d= 1-R;
    putting_pixel(x0+x, y0-y, WHITE, x_pivot, y_pivot, angle);
    while(x<=y)
    {
         x++;
        if(d<0)
        {
            d+=(2*x+3);
        }
        else
        {
            y--;
            d+=(2*x-2*y+5);

        }

        putting_pixel(x0+x, y0-y, c1, x_pivot, y_pivot, angle);
        putting_pixel(x0+y, y0-x, c2, x_pivot, y_pivot, angle);
        putting_pixel(x0+y, y0+x, c3, x_pivot, y_pivot, angle);
        putting_pixel(x0-x, y0-y, c4, x_pivot, y_pivot, angle);
        putting_pixel(x0-y, y0+x, c5, x_pivot, y_pivot, angle);
        putting_pixel(x0+x, y0+y, c6, x_pivot, y_pivot, angle);
        putting_pixel(x0-x, y0+y, c7, x_pivot, y_pivot, angle);
        putting_pixel(x0-y, y0-x, c8, x_pivot, y_pivot, angle);
    }
   //putpixel(x0+x, y0-y, WHITE);
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    int c1 = WHITE, c2 = BLACK;
//int rad = 0;
   for(int rad = 0; rad <360; rad++)
   {
        int x_pivot = 320, y_pivot = 240;
        c1 = WHITE, c2 = BLACK;
    makeCircle(320, 150, 30, c1, c1, c1, c2, c2, c1, c2, c2, x_pivot, y_pivot, rad);
    makeCircle(320, 210, 30, c2, c2, c2, c1, c1, c2, c1, c1, x_pivot, y_pivot, rad);
    makeCircle(320, 270, 30, c1, c1, c1, c2, c2, c1, c2, c2, x_pivot, y_pivot, rad);
    makeCircle(320, 330, 30, c2, c2, c2, c1, c1, c2, c1, c1, x_pivot, y_pivot, rad);
    makeCircle(230, 240, 30, c1, c1, c2, c1, c2, c2, c2, c1, x_pivot, y_pivot, rad);
    makeCircle(290, 240, 30, c2, c2, c1, c2, c1, c1, c1, c2, x_pivot, y_pivot, rad);
    makeCircle(350, 240, 30, c1, c1, c2, c1, c2, c2, c2, c1, x_pivot, y_pivot, rad);
    makeCircle(410, 240, 30, c2, c2, c1, c2, c1, c1, c1, c2, x_pivot, y_pivot, rad);
    makeCircle(320, 180, 60, c2, c2, c2, c1, c1, c2, c1, c1, x_pivot, y_pivot, rad);
    makeCircle(320, 300, 60, c1, c1, c1, c2, c2, c1, c2, c2, x_pivot, y_pivot, rad);
    makeCircle(260, 240, 60, c2, c2, c1, c2, c1, c1, c1, c2, x_pivot, y_pivot, rad);
    makeCircle(380, 240, 60, c1, c1, c2, c1, c2, c2, c2, c1, x_pivot, y_pivot, rad);
    delay(0.001);
    cleardevice();
    //c1 = BLACK, c2 = BLACK;
    /*
    makeCircle(320, 150, 30, c1, c1, c1, c2, c2, c1, c2, c2, x_pivot, y_pivot, rad);
    makeCircle(320, 210, 30, c2, c2, c2, c1, c1, c2, c1, c1, x_pivot, y_pivot, rad);
    makeCircle(320, 270, 30, c1, c1, c1, c2, c2, c1, c2, c2, x_pivot, y_pivot, rad);
    makeCircle(320, 330, 30, c2, c2, c2, c1, c1, c2, c1, c1, x_pivot, y_pivot, rad);
    makeCircle(230, 240, 30, c1, c1, c2, c1, c2, c2, c2, c1, x_pivot, y_pivot, rad);
    makeCircle(290, 240, 30, c2, c2, c1, c2, c1, c1, c1, c2, x_pivot, y_pivot, rad);
    makeCircle(350, 240, 30, c1, c1, c2, c1, c2, c2, c2, c1, x_pivot, y_pivot, rad);
    makeCircle(410, 240, 30, c2, c2, c1, c2, c1, c1, c1, c2, x_pivot, y_pivot, rad);

    makeCircle(320, 180, 60, c2, c2, c2, c1, c1, c2, c1, c1, x_pivot, y_pivot, rad);
    makeCircle(320, 300, 60, c1, c1, c1, c2, c2, c1, c2, c2, x_pivot, y_pivot, rad);
    makeCircle(260, 240, 60, c2, c2, c1, c2, c1, c1, c1, c2, x_pivot, y_pivot, rad);
    makeCircle(380, 240, 60, c1, c1, c2, c1, c2, c2, c2, c1, x_pivot, y_pivot, rad);
*/
   // delay(100);
    }
    getch();
    closegraph();
}
