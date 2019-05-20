#include <iostream>
#include <graphics.h>
#include<math.h>


#define ox1 54//107
#define oy1 120
#define ox2 267//320
#define ox3 480//533
#define oy2 360

using namespace std;


float cube[8][4] = {
	{0,0,0,1},//A 0
	{75,0,0,1},//B 1
	{75,75,0,1},//C 2
	{0,75,0,1},//D 3
	{0,0,75,1},//E 4
	{75,0,75,1},//F 5
	{75,75,75,1},//G 6
	{0,75,75,1}//H 7
};

void init(){
	int X = getmaxx();
	int Y = getmaxy();
	setcolor(2);
	line(0,Y/2,X,Y/2);
	line(X/3,0,X/3,Y);
	line((2*X)/3,0,(2*X)/3,Y);
}

void frontView(float cube[][4]){
	setcolor(4);
	for(int i=0;i<4;i++){
		line(ox1+cube[i][0],oy1-cube[i][1],ox1+cube[(i+1)%4][0],oy1-cube[(i+1)%4][1]);
		line(ox1+cube[4+i][0],oy1-cube[4+i][1],ox1+cube[4+((i+1)%4)][0],oy1-cube[4+((i+1)%4)][1]);
		line(ox1+cube[i][0],oy1-cube[i][1],ox1+cube[i+4][0],oy1-cube[i+4][1]);
	}
	outtextxy(ox1-30,oy1+100,"Front View(from +Z)");
}

void sideView(float cube[][4]){
	setcolor(4);
	for(int i=0;i<4;i++){
		line(ox2+cube[i][2],oy1-cube[i][1],ox2+cube[(i+1)%4][2],oy1-cube[(i+1)%4][1]);
		line(ox2+cube[4+i][2],oy1-cube[4+i][1],ox2+cube[4+((i+1)%4)][2],oy1-cube[4+((i+1)%4)][1]);
		line(ox2+cube[i][2],oy1-cube[i][1],ox2+cube[i+4][2],oy1-cube[i+4][1]);
	}
	outtextxy(ox2-30,oy1+100,"Side View(from +X)");
}

void topView(float cube[][4]){
	setcolor(4);
	for(int i=0;i<4;i++){
		line(ox3+cube[i][0],oy1-cube[i][2],ox3+cube[(i+1)%4][0],oy1-cube[(i+1)%4][2]);
		line(ox3+cube[4+i][0],oy1-cube[4+i][2],ox3+cube[4+((i+1)%4)][0],oy1-cube[4+((i+1)%4)][2]);
		line(ox3+cube[i][0],oy1-cube[i][2],ox3+cube[i+4][0],oy1-cube[i+4][2]);
	}
	outtextxy(ox3-30,oy1+100,"Top View(from +Y)");
}

void multiply(float cube[8][4],double op[4][4] ){
	int newMat[8][4];
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++)
			newMat[i][j]=0;
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				newMat[i][j]+=cube[i][k]*op[k][j];
			}
		}
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++)
			cube[i][j] = newMat[i][j];
	}
}

void rotX(float cube[8][4], int degree){
	double rad = 3.14/180.0 * (float)degree;
	double rotMat[4][4];
	int res[8][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			if(i!=j)
				rotMat[i][j]=0;
			else
				rotMat[i][j]=1;
	}
	double cs = cos(rad);
	double sn = sin(rad);
	rotMat[1][1]=cs;
	rotMat[2][2]=cs;
	rotMat[1][2]=-1.0*sn;
	rotMat[2][1]=sn;
	multiply(cube,rotMat);
}

void rotX(float cube[8][4], double cosT, double sinT){
	double rotMat[4][4];
	int res[8][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			if(i!=j)
				rotMat[i][j]=0;
			else
				rotMat[i][j]=1;
	}
	double cs = cosT;
	double sn = sinT;
	rotMat[1][1]=cs;
	rotMat[2][2]=cs;
	rotMat[1][2]=-1.0*sn;
	rotMat[2][1]=sn;
	multiply(cube,rotMat);
}

void rotY(float cube[8][4], int degree){
	double rad = 3.14/180.0 * (float)degree;
	double rotMat[4][4];
	int res[8][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			if(i!=j)
				rotMat[i][j]=0;
			else
				rotMat[i][j]=1;
	}
	double cs = cos(rad);
	double sn = sin(rad);
	rotMat[0][0]=cs;
	rotMat[2][2]=cs;
	rotMat[0][2]=sn;
	rotMat[2][0]=-1*sn;
	multiply(cube,rotMat);
}

void rotY(float cube[8][4], double cosT, double sinT){
	double rotMat[4][4];
	int res[8][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			if(i!=j)
				rotMat[i][j]=0;
			else
				rotMat[i][j]=1;
	}
	double cs = cosT;
	double sn = sinT;
	rotMat[0][0]=cs;
	rotMat[2][2]=cs;
	rotMat[0][2]=sn;
	rotMat[2][0]=-1*sn;
	multiply(cube,rotMat);
}


void rotZ(float cube[8][4], int degree){
	double rad = 3.14/180.0 * (float)degree;
	double rotMat[4][4];
	int res[8][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			if(i!=j)
				rotMat[i][j]=0;
			else
				rotMat[i][j]=1;
	}
	double cs = cos(rad);
	double sn = sin(rad);
	rotMat[0][0]=cs;
	rotMat[1][1]=cs;
	rotMat[0][1]=-1*sn;
	rotMat[1][0]=sn;
	multiply(cube,rotMat);
}

void rotZ(float cube[8][4], double cosT, double sinT){
	double rotMat[4][4];
	int res[8][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			if(i!=j)
				rotMat[i][j]=0;
			else
				rotMat[i][j]=1;
	}
	double cs = cosT;
	double sn = sinT;
	rotMat[0][0]=cs;
	rotMat[1][1]=cs;
	rotMat[0][1]=-1*sn;
	rotMat[1][0]=sn;
	multiply(cube,rotMat);
}

void isometricView(float cube[8][4]){
	float cube1[8][4];
	for(int i=0;i<8;i++){
		for(int j=0;j<4;j++){
			cube1[i][j] = cube[i][j];
		}
	}
	setcolor(4);
	rotY(cube1,-45);
	rotX(cube1,sqrt(2.0/3.0),sqrt(1.0/3.0));

	for(int i=0;i<4;i++){
		line(ox1+cube1[i][0],oy2-cube1[i][1],ox1+cube1[(i+1)%4][0],oy2-cube1[(i+1)%4][1]);
		line(ox1+cube1[4+i][0],oy2-cube1[4+i][1],ox1+cube1[4+((i+1)%4)][0],oy2-cube1[4+((i+1)%4)][1]);
		line(ox1+cube1[i][0],oy2-cube1[i][1],ox1+cube1[i+4][0],oy2-cube1[i+4][1]);
	}
	outtextxy(ox1-30,oy2+100,"Isometric View");
}

int main(){
	int gd = DETECT, gn;
	initgraph(&gd,&gn,NULL);
	init();
	frontView(cube);
	sideView(cube);
	topView(cube);
	isometricView(cube);
	int c;
	cin>>c;
	closegraph();
}
