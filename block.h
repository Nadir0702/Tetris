#ifndef BLOCK_H
#define BLOCK_H
#include "point.h"

class Tetris; // Forward declaration

class Block
{
    // Array representing possible block orientations
    static constexpr int ORIENTATIONS[4] = { 0, 1, 2, 3 };

    // Current block orientation
    int orientation;

    // Type of tetris shape
    GameConfig::eShapes shape;

    // Array of points representing the block
    Point points[GameConfig::BLOCK_SIZE];

    // Color of the block
    int color;

    // Private helper function to rotate the block
    void rotate(GameConfig::eCommands direction);

    // Private helper functions for specific shape rotations
    void rotateI(GameConfig::eCommands direction);
    void rotateL(GameConfig::eCommands direction);
    void rotateS(GameConfig::eCommands direction);
    void rotateZ(GameConfig::eCommands direction);
    void rotatePlus(GameConfig::eCommands direction);
    void rotateReverseL(GameConfig::eCommands direction);

    // Reset the block's properties
    void resetPoints();

public:

    // Constructor: Initializes the block with default properties
    Block(bool& isInColor) : points() { reset(isInColor); }

    // Getter for block color
    int getColor() { return color; }

    // Reset the block to its default state
    void reset(bool& isInColor);

    // Draw the block on the screen
    void draw(const char& ch, const int& drawOffset);

    // Move the block based on the specified direction
    void move(GameConfig::eCommands direction);

    // Reverse a previous move based on the specified direction
    void unMove(GameConfig::eCommands direction);

    // Get an array of points representing the block
    void getPoints(Point* pointsArr);
};

#endif // !BLOCK_H