#include "snow.h"

int main() {
    HDC desktop = GetDC(NULL);
    int screenX = GetSystemMetrics(SM_CXSCREEN);
    int screenY = GetSystemMetrics(SM_CYSCREEN);
    double chance = 0.2;

    snowflake snowflakesI[3000];
    int distance[3000][2];
    int gX, gY;
    //Init snowflakes
    for (int i = 0; i < 1500; i++) {
        gX = rand() % screenX;
        gY = rand() % screenY;
        if (allCheckDist(gX, gY, i * 2 - 1, distance)) {
            snowflakesI[i].init(gX, gY, screenX, screenY, desktop, 0xFFFFFF, 0);
            distance[i][0] = gX;
            distance[i][1] = gY;
        }
        else {
            i--;
        }
    }
    //Draw snowflakes
    while(true) {
        for (int i = 0; i < 1500; i++) {
            snowflakesI[i].draw();
        }
    }
}