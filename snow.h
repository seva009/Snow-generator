#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H
//Interface header

#include <windows.h>

bool checkdistance(int x1, int y1, int x2, int y2);
bool allCheckDist(int x1, int y1, int len, int (*other)[2]);

struct snowflake {
    int realX;
    int realY;
    int maxX;
    int maxY;
    COLORREF replacedColors[6];
    COLORREF sfColor;
    short cFrame;
    HDC desktop;

    void init(int _realX, int _realY, int _maxX, int _maxY, HDC _desktop, COLORREF _sfColor, int _cFrame);
    void draw();
};

#endif // SNOWFLAKE_H