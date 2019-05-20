#include<graphics.h>
#include<iostream>
#include<math.h>
#define PI 3.148
using namespace std;
void point(int x, int y, int ox, int oy, int color){
	if(ox+x>=0 && oy-y>=0 && ox+x<getmaxx() && oy-y<getmaxy())
		putpixel(ox+x,oy-y,color);
	else
		cout<<ox+x<<","<<oy-y<<" : Pixel out of bound\n";//display a point x,y with respect to origin at ox,oy
}

void ellipsePoint(int x, int y, int ox, int oy, int color){
	point(x,y,ox,oy,color);
	point(x,-1*y,ox,oy,color);
	point(-1*x, -1*y, ox,oy,color);
	point(-1*x,y,ox,oy,color);
}

void drawEllipse(int cx, int cy,int a, int b,int color){
	double d2;
	int x=0;
	int y=b;
	double dl=b*b - (a*a*b) + 0.25*a*a;
	ellipsePoint(x,y,cx,cy,color);
	while(a*a*(y-0.5)>b*b*(x+1)){
		if(dl<0){
			dl+=(b*b*(2*x+3));
		}else{
			dl+=((b*b*(2*x+3))+(a*a*(-2*y+2)));
			y--;
		}
		x++;
		ellipsePoint(x,y,cx,cy,color);
	}
	d2 = b*b*(x+0.5)*(x+0.5) + a*a*(y-1)*(y-1)-a*a*b*b;
	while(y>0){
		if(d2<0){
			d2 += ((b*b*(2*x+2))+(a*a*(-2*y+3)));
			x++;
		}else{
			d2 += (a*a*(-2*y + 3));
		}
		y--;
		ellipsePoint(x,y,cx,cy,color);
	}
}

int main()
{
	int gd = DETECT, gn,x,y,a,b;
	initgraph(&gd,&gn,NULL);
	int X = getmaxx();
	int Y = getmaxy();
	setcolor(WHITE);
	line(0,Y/2,X,Y/2);// x axis
	line(X/2,0,X/2,Y);// y axis
	setcolor(WHITE);
	cout<<"Enter x y a b : \n";
	cin>>x>>y>>a>>b;
	drawEllipse(X/2+x,Y/2-y,a,b,WHITE);
	//drawCircle(X/2,Y/2,X/4,3);
	//drawCircle(X/2,Y/2,X/8,4);
	char c;
	cin>>c;
	closegraph();
}
