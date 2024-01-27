#ifndef POINT_H
#define POINT_H

#include "gameConfig.h"

class Tetris; // Forward declaration

class Point
{
    int x;
    int y;
    int diff_x;
    int diff_y;

public:

    // Constructor with default values
    Point(int _x = 6, int _y = 0);

    // Draw the point on the screen
    void draw(const char& ch, const int& drawOffset, int color);

    // Move the point based on the specified direction
    void move(GameConfig::eCommands direction);

    // Setter for X coordinate
    void setX(int x) { this->x = x; }

    // Setter for Y coordinate
    void setY(int y) { this->y = y; }

    // Getter for X coordinate
    int getX() { return x; }

    // Getter for Y coordinate
    int getY() { return y; }
};

#endif // !POINT_H