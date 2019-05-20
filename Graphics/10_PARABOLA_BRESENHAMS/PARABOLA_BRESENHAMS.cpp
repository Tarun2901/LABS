#include <iostream>
#include <graphics.h>
#include <math.h>

#define PI 3.148

using namespace std;


void point(int x, int y, int ox, int oy, int color){
	if(ox+x>=0 && oy-y>=0 && ox+x<getmaxx() && oy-y<getmaxy())
		putpixel(ox+x,oy-y,color);
	else
		cout<<ox+x<<","<<oy-y<<" : Pixel out of bound\n";//display a point x,y with respect to origin at ox,oy
}

void parabolaPointX(int x, int y, int ox, int oy, int color){
	point(x,y,ox,oy,color);
	point(x,-y,ox,oy,color);
}

void parabolaPointY(int x, int y, int ox, int oy, int color){
	point(x,y,ox,oy,color);
	point(-1*x,y,ox,oy,color);
}

void drawParabolaX(int cx, int cy, double a, int color){
	double a1 = a;
	if(a1<=0){
		//cout<<"This parabola is not defined yet!\n";
		//return;
		a = -1*a;
	}
	const int X = getmaxx();
	const int Y = getmaxy();

	int x=0;
	int y=0;
	double d1 = 1.0 - 2.0*a;
	parabolaPointX(x,y,cx,cy,color);
	while(y<2*a){
		if(d1<0){
			d1 = d1 + 2.0*y + 3.0;
		}else{
			d1 = d1 + 2.0*y + 3 -4.0*a;
			x++;
		}
		y++;
		if(a1>0)
			parabolaPointX(x,y,cx,cy,color);
		else
			parabolaPointX(-1*x,y,cx,cy,color);
	}
	double d2 = (y+0.5)*(y+0.5) - 4.0*a*(x+1);
	while(x+cx < X && cy-y>0){
		if(d2<0){
			d2 = d2+2.0*(y+1)-4.0*a;
			y++;
		}else{
			d2 = d2-4.0*a;
		}
		x++;
		if(a1>0){
			parabolaPointX(x,y,cx,cy,color);
		}else{
			parabolaPointX(-1*x,y,cx,cy,color);
		}
	}
}

void drawParabolaY(int cx, int cy, double a, int color){
	double a1 = a;
	if(a1<=0){
		//cout<<"This parabola is not defined yet!\n";
		//return;
		a = -1*a;
	}
	const int X = getmaxx();
	const int Y = getmaxy();

	int x=0;
	int y=0;
	double d1 = 1.0 - 2.0*a;
	parabolaPointY(x,y,cx,cy,color);
	while(y<2*a){
		if(d1<0){
			d1 = d1 + 2.0*y + 3.0;
		}else{
			d1 = d1 + 2.0*y + 3 -4.0*a;
			x++;
		}
		y++;
		if(a1>0)
			parabolaPointY(y,x,cx,cy,color);
		else
			parabolaPointY(y,-1*x,cx,cy,color);
	}
	double d2 = (y+0.5)*(y+0.5) - 4.0*a*(x+1);
	while(x+cx < X && cy-y>0){
		if(d2<0){
			d2 = d2+2.0*(y+1)-4.0*a;
			y++;
		}else{
			d2 = d2-4.0*a;
		}
		x++;
		if(a1>0){
			parabolaPointY(y,x,cx,cy,color);
		}else{
			parabolaPointY(y,-1*x,cx,cy,color);
		}
	}
}

int main(){
	int gd=DETECT, gn;
	initgraph(&gd,&gn,NULL);
	setcolor(2);
	const int X = getmaxx();
	const int Y = getmaxy();

	line(0,Y/2,X,Y/2);// x axis
	line(X/2,0,X/2,Y);// y axis
	setcolor(1);
	drawParabolaX(X/2,Y/2,-10,3);
	drawParabolaY(X/2,Y/2,-10,3);
	drawParabolaX(X/2,Y/2,10,3);
	drawParabolaY(X/2,Y/2,10,3);
	int c;
	cin>>c;
	closegraph();
}

