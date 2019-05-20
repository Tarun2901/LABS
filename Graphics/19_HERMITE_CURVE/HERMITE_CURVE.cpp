#include<iostream>
#include "graphics.h"

using namespace std;

//float P0x = 100, P0y = 100, P1x = 150, P1y = 50, P2x = 250, P2y = 200, P3x = 350, P3y = 40, Px= 0, Py = 0, Pz = 0;
float P0x = 40, P0y = 250, P1x = 40, P1y = 200, P2x = 40, P2y = 150, P3x = 40, P3y = 100, Px= 0, Py = 0, Pz = 0;

void calcP(float &Px, float &Py, float &Pz, float t){
    Px = (-4.5 * t * t* t + 9*t*t - 5.5 *t +1)*P0x + (13.5 * t*t*t - 22.5 *t*t +9*t)*P1x + (-13.5 * t*t*t + 18*t*t -4.5*t)*P2x +(4.5*t*t*t -4.5*t*t +t)*P3x;
    Py = (-4.5 * t * t* t + 9*t*t - 5.5 *t +1)*P0y + (13.5 * t*t*t - 22.5 *t*t +9*t)*P1y + (-13.5 * t*t*t + 18*t*t -4.5*t)*P2y +(4.5*t*t*t -4.5*t*t +t)*P3y;
//    Pz = (-4.5 * t * t* t + 9*t*t - 5.5 *t +1)*P0z + (13.5 * t*t*t - 22.5 *t*t +9*t)*P1z + (-13.5 * t*t*t + 18*t*t -4.5*t)*P2z +(4.5*t*t*t -4.5*t*t +t)*P3z;
}

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    float t = 0;

    ///po
    t = 0;
    P0x = 170, P0y = 250, P1x = 170, P1y = 200, P2x = 170, P2y = 150, P3x = 170, P3y = 100, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }


    t = 0;
    P0x = 90, P0y = 100, P1x = 105, P1y = 150, P2x = 150, P2y = 160, P3x = 170, P3y = 100, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    t = 0;
    P0x = 170, P0y = 250, P1x = 155, P1y = 260, P2x = 155, P2y = 275, P3x = 170, P3y = 290, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    t = 0;
    P0x = 170, P0y = 250, P1x = 190, P1y = 265, P2x = 210, P2y = 280, P3x = 240, P3y = 295, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    t = 0;
    P0x = 170, P0y = 290, P1x = 180, P1y = 280, P2x = 185, P2y = 270, P3x = 190, P3y = 265, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }


    ///ja

    t = 0;
    P0x = 330, P0y = 250, P1x = 330, P1y = 200, P2x = 330, P2y = 150, P3x = 330, P3y = 100, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    t = 0;
    P0x = 380, P0y = 250, P1x = 380, P1y = 200, P2x = 380, P2y = 150, P3x = 380, P3y = 100, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    t = 0;
    P0x = 200, P0y = 150, P1x = 210, P1y = 190, P2x = 260, P2y = 200, P3x = 250, P3y = 165, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    ///j
    t = 0;
    P0x = 250, P0y = 165, P1x = 280 , P1y = 165, P2x = 310, P2y = 165, P3x = 330, P3y = 165, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    t = 0;
    P0x = 60, P0y = 100, P1x = 170 , P1y = 100, P2x = 270, P2y = 100, P3x = 420, P3y = 100, Px= 0, Py = 0, Pz = 0;
    while(t<1){
        calcP(Px, Py, Pz, t);
        t+=0.001;
        putpixel(Px, Py, WHITE);
    }

    getch();
    closegraph();
    return 0;
}
