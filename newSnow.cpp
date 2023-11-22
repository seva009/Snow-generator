#include <windows.h>
#include <cmath>
#include <omp.h>
#include <iostream>
using namespace std;

typedef struct {
    int x, y;
    int screenX, screenY;
    int size;
    double speed;
    double angle;
    COLORREF color;
    HDC desktop;
    void render() {
        SetPixelV(desktop, x, y, color);
        x += round(speed * cos(angle));
        y += round(speed * sin(angle));
        y += (rand() % 10) * speed / abs(speed);
        if (x < 0 || x > screenX)
            speed *= -1;
        if (y < 0 || y > screenY)
            speed *= -1;
        color = GetPixel(desktop, x, y);
        SetPixelV(desktop, x, y, 0xffffff);
    }
    void init(int _x, int _y, int _screenX, int _screenY, int _size, double _speed, double _angle, COLORREF _color, HDC _desktop) {
        x = _x;
        y = _y;
        screenX = _screenX;
        screenY = _screenY;
        desktop = _desktop;
        size = _size;
        speed = _speed;
        angle = _angle;
        color = GetPixel(desktop, x, y);
    }
}  snow; 

int main() {
    int screenX = GetSystemMetrics(SM_CXSCREEN);
    int screenY = GetSystemMetrics(SM_CYSCREEN);
    HDC desktop = GetDC(NULL);
    snow snows[10000];
    //omp_set_num_threads(8);
    //#pragma omp parallel for
    for (int i = 0; i < 10000; i++) {
        snows[i].init(rand() % screenX,
                      rand() % screenY,
                      screenX, 
                      screenY, 
                      rand() % 5 + 5, 
                      rand() % 5 + 5, 
                      rand() % 360, 
                      0xffffff,
                      desktop);
    }
    while (true) {
        for (int i = 0; i < 10000; i++) {
            snows[i].render();
        }
    }
}
