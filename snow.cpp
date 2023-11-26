#include <windows.h>
#include <math.h>
#include "snow.h"

/**
 * Calculates the distance between two points in a 2D plane.
 *
 * @param x1 The x-coordinate of the first point.
 * @param y1 The y-coordinate of the first point.
 * @param x2 The x-coordinate of the second point.
 * @param y2 The y-coordinate of the second point.
 *
 * @return True if the distance between the two points is greater than 9, false otherwise.
 *
 * @throws None
 */
bool checkdistance(int x1, int y1, int x2, int y2) {
    int d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if (d > 9) {
        return true;
    }
    return false;
}

/**
 * Checks if all the given points are at a certain distance from a reference point.
 *
 * @param x1 the x-coordinate of the reference point
 * @param y1 the y-coordinate of the reference point
 * @param len the number of points to check
 * @param other a 2D array containing the coordinates of the other points
 *
 * @return true if all points are at the specified distance from the reference point, false otherwise
 *
 * @throws None
 */
bool allCheckDist(int x1, int y1, int len, int (*other)[2]) {
    for (int i = 0; i < len; i++) {
        if (!checkdistance(x1, y1, other[i][0], other[i][1])) {
            return false;
        }
    }
    return true;
}

/**
 * Initializes the snowflake object with the given parameters.
 *
 * @param _realX the x-coordinate of the snowflake's position
 * @param _realY the y-coordinate of the snowflake's position
 * @param _maxX the maximum x-coordinate value for the snowflake's position
 * @param _maxY the maximum y-coordinate value for the snowflake's position
 * @param _desktop the handle to the desktop window
 * @param _sfColor the color of the snowflake
 * @param _cFrame the current frame number
 *
 * @throws ErrorType if an error occurs during initialization
 */
void snowflake::init(int _realX, int _realY, int _maxX, int _maxY, HDC _desktop, COLORREF _sfColor, int _cFrame) {
    cFrame = _cFrame;
    desktop = _desktop;
    sfColor = _sfColor;
    realX = _realX;
    realY = _realY;
    maxX = _maxX;
    maxY = _maxY;
}

/**
 * Draws a snowflake with given parameters on the screen.
 *
 * @throws None
 */
void snowflake::draw() {
    if (realX <= maxX && realY <= maxY) {
        if (!cFrame) {
            SetPixel(desktop, realX + 1, realY + 1, replacedColors[0]);
            SetPixel(desktop, realX + 1, realY - 1, replacedColors[1]);
            SetPixel(desktop, realX, realY, replacedColors[2]);
            SetPixel(desktop, realX - 1, realY - 1, replacedColors[3]);
            SetPixel(desktop, realX - 1, realY + 1, replacedColors[4]);
            realY+=4;
            replacedColors[0] = GetPixel(desktop, realX + 1, realY);
            replacedColors[1] = GetPixel(desktop, realX - 1, realY);
            replacedColors[2] = GetPixel(desktop, realX, realY + 1);
            replacedColors[3] = GetPixel(desktop, realX, realY - 1);
            SetPixel(desktop, realX + 1, realY, sfColor);
            SetPixel(desktop, realX - 1, realY, sfColor);
            SetPixel(desktop, realX, realY + 1, sfColor);
            SetPixel(desktop, realX, realY - 1, sfColor);
            cFrame++;
        }
        else {
            SetPixel(desktop, realX + 1, realY, replacedColors[0]);
            SetPixel(desktop, realX - 1, realY, replacedColors[1]);
            SetPixel(desktop, realX, realY + 1, replacedColors[2]);
            SetPixel(desktop, realX, realY - 1, replacedColors[3]);
            realY+=4;
            replacedColors[0] = GetPixel(desktop, realX + 1, realY + 1);
            replacedColors[1] = GetPixel(desktop, realX + 1, realY - 1);
            replacedColors[2] = GetPixel(desktop, realX, realY);
            replacedColors[3] = GetPixel(desktop, realX - 1, realY - 1);
            replacedColors[4] = GetPixel(desktop, realX - 1, realY + 1);
            sfColor = 0xffffff;
            SetPixel(desktop, realX + 1, realY + 1, sfColor);
            SetPixel(desktop, realX + 1, realY - 1, sfColor);
            SetPixel(desktop, realX, realY, sfColor);
            SetPixel(desktop, realX - 1, realY - 1, sfColor);
            SetPixel(desktop, realX - 1, realY + 1, sfColor);
            cFrame = 0;
        }
    }
    else {
        realY = 0;
    }
}