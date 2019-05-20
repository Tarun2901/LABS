#include<graphics.h>
#include<iostream>
using namespace std;
void point(int x, int y, int ox, int oy, int color=WHITE){
	if(ox+x>=0 && oy-y>=0 && ox+x<getmaxx() && oy-y<getmaxy())
		putpixel(ox+x,oy-y,color);
	else
		cout<<ox+x<<","<<oy-y<<" : Pixel out of bound\n";//display a point x,y with respect to origin at ox,oy
}
void drawLine(int x1, int y1, int x2, int y2,int ox,int oy, int color=WHITE)//line between x1,y1 and x2,y2 with ox,oy as origin and color
{
	int xl, yl, xr, yr, dx, dy;
	if(x1<x2)
	{
		xl = x1;
		yl = y1;
		xr = x2;
		yr = y2;
	}
	else
	{
		xl = x2;
		yl = y2;
		xr = x1;
		yr = y1;
	}
	cout<<xl<<","<<yl<<","<<xr<<","<<yr<<"\n";
	dx = xr - xl;
	dy = yr - yl;
	cout<<dx<<" "<<dy<<"\n";
	/*If line is vertical*/
	if(dx==0)
	{
		int yt=(yl>yr)?yl:yr;
		int yb=(yl>yr)?yr:yl;
		cout<<yb<<","<<yt<<"\n";
		while(yb<=yt){
			cout<<yb<<"\n";
			point(xr,yb,ox,oy,color);
			yb++;
		}
	}
	/*If line is horizontal*/
	else if(dy==0)
	{
		cout<<xl<<","<<xr<<"\n";
		while(xl<=xr){
			cout<<xl<<"\n";
			point(xl,yr,ox,oy,color);
			xl++;
		}
	}

	double m = (double)dy/dx;
	/*Angle less than 45 deg and more than 0 deg*/
	if(m>0 && m<=1)
	{
		int D = -2*dy + dx;
		int dNE = 2*dx - 2*dy;
		int dE = -2*dy;
		point(xl,yl,ox,oy,color);
		while(xl<=xr){
			if(D<0){
				yl++;
				D = D+dNE;
			}else{
				D = D+dE;
			}
			xl++;
			point(xl,yl,ox,oy,color);
		}
	}
	/*Angle more than 45 deg and less than 90 deg*/
	else if(m>1)
	{
		int D = 2*dx - dy;
		int dN = 2*dx;
		int dNE = 2*dx - 2*dy;
		point(xl,yl,ox,oy,color);
		while(yl<=yr){
			if(D<0){
				D+=dN;
			}else{
				xl++;
				D+=dNE;
			}
			yl++;
			point(xl,yl,ox,oy,color);
		}
	}
	/*Angle less than 0 deg and more than -45 deg*/
	else if(m<0 && m>=-1)
	{

		int D = 2*dy + dx;
		int dSE = 2*dx + 2*dy;
		int dE = 2*dy;
		point(xl,yl,ox,oy,color);
		while(xl<=xr){
			if(D<0){
				D = D+dE;
			}else{
				yl--;
				D = D+dSE;
			}
			xl++;
			point(xl,yl,ox,oy,color);
		}
	}
	/*Angle less than -45 deg but more than -90 deg*/
	else if(m<-1)
	{
		cout<<"Slope more than -1\n";
		int D = 2*dx - dy;
		int dS = -2*dx;
		int dSE = -2*dx - 2*dy;
		point(xl,yl,ox,oy,color);
		while(yl>=yr){
			if(D<0){
				D+=dS;
			}else{
				xl++;
				D+=dSE;
			}
			yl--;
			point(xl,yl,ox,oy,color);
		}
	}

}

int main(){
	int gd=DETECT, gn;
	initgraph(&gd,&gn,NULL);
	int X = getmaxx();
	int Y = getmaxy();
	int x1,y1,x2,y2;
	setcolor(WHITE);
	line(0,Y/2,X,Y/2);// x axis
	line(X/2,0,X/2,Y);// y axis
	setcolor(WHITE);
	cout<<"Line 1 : x1 y1 x2 y2 : ";
	cin>>x1>>y1>>x2>>y2;
	drawLine(x1,y1,x2,y2,X/2,Y/2,WHITE);
	getch();
	closegraph();
}
