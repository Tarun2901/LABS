#include<math.h>
#include<graphics.h>
#define pi 3.14

float prism[4][8]= {{0, 80, 80, 0, 20, 60, 60, 20},
                    {80, 80, 0, 0, 60, 60, 20, 20},
                    {0, 0, 0, 0, -60, -60, -60, -60},
                    {1, 1, 1, 1, 1, 1, 1, 1}    };

float dot(float n1[],float n2[])
{
    int i;
    float ans=0;
    for(i=0; i<3; i++) {
        ans+=(n1[i]*n2[i]);
    }
    return ans;
}

float mag(float n[])
{
    return(sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]));
}

void normal(float n[],int a,int b,int c,int s1,int s2)
{
    int i;
    float n1[3],n2[3],n3[3],v[3],cos;
    for(i=0; i<3; i++) {
        n1[i]=prism[i][a];
        n2[i]=prism[i][b];
        n3[i]=prism[i][c];
        v[i]=prism[i][s1]-prism[i][s2];
    }
    n[0]=((n1[1]-n2[1])*(n2[2]-n3[2]))-((n1[2]-n2[2])*(n2[1]-n3[1]));
    n[1]=((n1[2]-n2[2])*(n2[0]-n3[0]))-((n1[0]-n2[0])*(n2[2]-n3[2]));
    n[2]=((n1[0]-n2[0])*(n2[1]-n3[1]))-((n1[1]-n2[1])*(n2[0]-n3[0]));
    cos=dot(n,v)/(mag(n)*mag(v));
    if(cos>0)
        for(i=0; i<3; i++)
            n[i]=n[i]*(-1);
}

void mp(float n[],int a,int b)
{
    int i;
    for(i=0; i<3; i++)
        n[i]=(prism[i][a]+prism[i][b])/2;
    n[2]-=32768;
}

void fline(int x0,int y0,int x1,int y1,int x2,int y2,int c1=15,int style=0)
{
    setcolor(c1);
    setlinestyle(style,1,1);
    line(x0+x1,y0-y1,x0+x2,y0-y2);
    setcolor(15);
    setlinestyle(0,1,1);
}

void surface(int x0,int y0,int t,float prism[][8],int color[])
{
    int i,j,style=0;
    float n[3],n2[3];
    if(t==0) {      //ABCD
        normal(n,0,1,2,4,0);
        mp(n2,0,2);
        if(dot(n,n2)>0)
            style=3;
        for(i=0; i<4; i++) {
            j=i+1;
            if(j==4)
                j=0;
            fline(x0,y0,prism[0][i],prism[1][i],prism[0][j],prism[1][j],color[t],style);
        }
        //setfillstyle(SOLID_FILL,color[t]);
    }
    else if(t==1) {     //EFGH
        normal(n,4,5,6,0,4);
        mp(n2,4,6);
        if(dot(n,n2)>0)
            style=3;
        for(i=4; i<8; i++) {
            j=i+1;
            if(j==8)
                j=4;
            fline(x0,y0,prism[0][i],prism[1][i],prism[0][j],prism[1][j],color[t],style);
        }
        //setfillstyle(SOLID_FILL,color[t]);
    }
    else if(t==2) {     //GFBC
        normal(n,6,5,1,4,5);
        mp(n2,6,1);
        if(dot(n,n2)>0)
            style=3;
        fline(x0,y0,prism[0][6],prism[1][6],prism[0][5],prism[1][5],color[t],style);//GF
        fline(x0,y0,prism[0][5],prism[1][5],prism[0][1],prism[1][1],color[t],style); //FB
        fline(x0,y0,prism[0][1],prism[1][1],prism[0][2],prism[1][2],color[t],style); //BC
        fline(x0,y0,prism[0][2],prism[1][2],prism[0][6],prism[1][6],color[t],style); //CG
        //setfillstyle(SOLID_FILL,color[t]);
    }
    else if(t==3) {//GCDH
        normal(n,6,2,3,5,6);
        mp(n2,6,3);
        if(dot(n,n2)>0)
            style=3;
        fline(x0,y0,prism[0][6],prism[1][6],prism[0][2],prism[1][2],color[t],style);//GC
        fline(x0,y0,prism[0][2],prism[1][2],prism[0][3],prism[1][3],color[t],style);//CD
        fline(x0,y0,prism[0][3],prism[1][3],prism[0][7],prism[1][7],color[t],style);//DH
        fline(x0,y0,prism[0][7],prism[1][7],prism[0][6],prism[1][6],color[t],style);//HG
        //setfillstyle(SOLID_FILL,color[t]);
    }
    else if(t==4) {     //AEFB
        normal(n,4,5,1,6,5);
        mp(n2,1,5);
        if(dot(n,n2)>0)
            style=3;
        fline(x0,y0,prism[0][0],prism[1][0],prism[0][4],prism[1][4],color[t],style);//AE
        fline(x0,y0,prism[0][4],prism[1][4],prism[0][5],prism[1][5],color[t],style);//EF
        fline(x0,y0,prism[0][5],prism[1][5],prism[0][1],prism[1][1],color[t],style);//FB
        fline(x0,y0,prism[0][1],prism[1][1],prism[0][0],prism[1][0],color[t],style);//BA
        //setfillstyle(SOLID_FILL,color[t]);
    }
    else if(t==5) {     //EADH
        normal(n,4,0,3,5,4);
        mp(n2,4,3);
        if(dot(n,n2)>0)
            style=3;
        fline(x0,y0,prism[0][4],prism[1][4],prism[0][0],prism[1][0],color[t],style);//EA
        fline(x0,y0,prism[0][0],prism[1][0],prism[0][3],prism[1][3],color[t],style);//AD
        fline(x0,y0,prism[0][3],prism[1][3],prism[0][7],prism[1][7],color[t],style);//DH
        fline(x0,y0,prism[0][7],prism[1][7],prism[0][4],prism[1][4],color[t],style);//HE
        //setfillstyle(SOLID_FILL,color[t]);

    }
}

void front(float prism[][8],int x0=320,int y0=240)
{
    int i;
    int color[6]= {15,15,15,15,15,15};
    for(i=0; i<6; i++)
        surface(x0,y0,i,prism,color);
}

int main()
{
    int gd = DETECT, gn;
    initgraph(&gd,&gn,NULL);
    front(prism);

    getch();
    return 0;
}
