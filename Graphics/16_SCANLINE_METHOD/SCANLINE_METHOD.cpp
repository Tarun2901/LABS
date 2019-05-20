#include <stdio.h>
#include <graphics.h>
#include <iostream>

using namespace std;

int main()
{
    int n, i, j, k, dy, dx;
    int x, y, temp;
    int xv[20], yv[20], xi[20];
    float slope[20];

    cout << "Enter the no. of edges of polygon : ";
    cin >> n;
    cout << "Enter the co-ordinates of polygon :\n";
    for (i = 0; i < n; i++) {
        printf("\tX%d Y%d : ",i,i);
        scanf("%d %d",&xv[i],&yv[i]);
    }
    xv[n]=xv[0];
    yv[n]=yv[0];
    int gd = DETECT, gn;
    initgraph(&gd,&gn,NULL);

    /* draw polygon */
    for (i = 0; i < n; i++) {
        line(xv[i],yv[i],xv[i+1],yv[i+1]);
        delay(50);
    }

    for (i = 0; i < n; i++) {
        dy = yv[i+1] - yv[i];
        dx = xv[i+1] - xv[i];
        if(dy==0)
            slope[i]=1.0;
        if(dx==0)
            slope[i]=0.0;
        if ((dy != 0) && (dx != 0)) {/*- calculate inverse slope -*/
            slope[i] = (float) dx / dy;
        }
    }
    for(y = 0; y < 480; y++) {
        k = 0;
        for (i=0;i<n;i++) {
            if (((yv[i] <= y) && (yv[i+1] > y)) || ((yv[i] > y) && (yv[i+1] <= y))) {
                xi[k] = (int)(xv[i] + slope[i] * (y - yv[i]));
                k++;
            }
        }
        for(j = 0; j < k - 1; j++) {/*- Arrange x-intersections in order -*/
            for(i = 0; i < k - 1; i++) {
                if(xi[i] > xi[i+1]) {
                    temp  =xi[i];
                    xi[i] = xi[i+1];
                    xi[i+1] = temp;
                }
            }
            setcolor(4);
            for(i = 0; i < k; i += 2) {
                line(xi[i], y, xi[i+1] + 1, y);
                delay(10);
            }
        }
    }

    getch();
    return 0;
}
