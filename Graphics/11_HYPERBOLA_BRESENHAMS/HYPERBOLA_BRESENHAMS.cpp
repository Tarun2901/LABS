#include <iostream>
#include <graphics.h>
#define CENX 320
#define CENY 240

using namespace std;

void hyperbola_point(int cx, int cy, int x, int y) {
    putpixel(CENX + cx + x, CENY - cy - y, WHITE);
    putpixel(CENX + cx + x, CENY - cy + y, WHITE);
    putpixel(CENX + cx - x, CENY - cy - y, WHITE);
    putpixel(CENX + cx - x, CENY - cy + y, WHITE);
}

void draw_hyperbola(int cx, int cy, int type, int a, int b, int xmax, int ymax)
{
    if (type == 1) {
        int x = a, y = 0;
        int d = 0.25 * b * b - a * a + a * b * b;
        hyperbola_point(cx, cy, x, y);

        while (b * b * x > a * a * y && x < xmax && y < ymax) {
            if (d < 0) {
                d += (b * b *(2 * x + 2) - a * a * (2 * y + 3));
                x++;
            }
            else {
                d -= (a * a *(2 * y + 3));
            }
            y++;
            hyperbola_point(cx, cy, x, y);
        }

        d = b*b*x*x + b*b + 2*b*b*x - a*a*y*y -0.25*a*a - a*a*y - a*a*b*b;

        while(x < xmax && y < ymax) {
            if(d > 0) {
                d += (b * b * (2 * x + 3) - a * a * (2 * y + 2));
                y++;
            }
            else {
                d += (b * b * (2 * x + 3));
            }
            x++;
            hyperbola_point(cx, cy, x, y);
        }
    }
    else {
        int y = b, x = 0;
        int d = -0.25 * a * a + b * b - b * a * a;
        hyperbola_point(cx, cy, x, y);

        while(a * a * y > b * b * x && x < xmax && y < ymax) {
            if(d < 0) {
                d += (a * a * (2 * y + 2) - b * b * (2 * x + 3));
                y++;
            }
            else {
                d -= (b * b * (2 * x + 3));
            }
            x++;
            hyperbola_point(cx, cy, x, y);
        }

        d = a*a*y*y + a*a + 2*a*a*y - b*b*x*x - 0.25*b*b - b*b*x - b*b*a*a;

        while (x < xmax && y < ymax) {
            if (d > 0) {
                d += (a*a*(2*y + 3) - b*b*(2*x + 2));
                x++;
            }
            else {
                d += (a*a*(2*y + 3));
            }
            y++;
            hyperbola_point(cx, cy, x, y);
        }
    }
}

int main()
{
    int gd = DETECT, gn;
    initgraph(&gd,&gn,NULL);
    int ch, a, b;
    line(320, 0, 320, 480);
    line(0, 240, 640, 240);
    cout << "Enter \n1 for horizontal hyperbola, and \n2 for vertical hyperbola : ";
    cin >> ch;
    cout<<"Enter the coordinates of the center of hyperbola : \n";
    int x,y;
    cin>>x>>y;
    cout << "Enter the value of a and b: ";
    cin >> a >> b;

    draw_hyperbola(x, y, ch, a, b, CENX, CENY);
    getch();
    return 0;
}
