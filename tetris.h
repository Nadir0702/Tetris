#ifndef TETRIS_H
#define TETRIS_H
#include "block.h"
#include"menu.h"

class Tetris
{
    Block currBlock; // Current block in play
    const char* keys; // Array of keys for player input
    char keyPressed; // Last key pressed by the player
    bool didLoose; // Flag indicating whether the player has lost
    bool shouldLock; // Flag indicating whether the block should be locked in place
    int drawOffset; // Offset used for drawing on the screen
    int score; // Player's score
    struct PIXEL
    {
        char ch;
        int color;
    };

    GameConfig::eCommands getDirection(); // Get the player's input direction
    void lockBlock(); // Lock the current block in place
    bool isPosValid(Point* ptArr, const GameConfig::eCommands& direction); // Check if the position is valid for the block
    bool isFullLine(int row); // Check if a line is full
    void copyLine(int read, int write); // Copy a line from one row to another
    void resetLine(int row); // Reset a line by clearing it

public:

    PIXEL grid[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT]; // Game grid representing the play area

    // Constructor: Initializes the Tetris game with player input keys and draw offset
    Tetris(const char* _keys, int _drawOffset, bool& isInColor);

    // Setter for didLoose flag
    void setDidLoose(bool _didLoose) { didLoose = _didLoose; }

    // Getter for didLoose flag
    bool getDidLoose() { return didLoose; }

    // Getter for the player's score
    int getScore() { return score; }

    // Process the player's input and update the game state
    void nextMove(const char input, bool& isInColor);

    // Clear the game state
    void clearGame(bool& isInColor);

    // Handle the removal of full lines and update the score
    void handleFullLine();

    // Draw the game board on the screen
    void drawBoard();

    // Check if a move is valid for the current block
    bool isValidMove(Block& block, const GameConfig::eCommands& direction);
};

#endif // !TETRIS_H