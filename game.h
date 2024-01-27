#ifndef GAME_H
#define GAME_H

#include "tetris.h"
#include "menu.h"

 /**
  * @class Game
  * @brief Manages the flow and rules of the Tetris game.
  */
class Game
{
private:
    /**
     * @brief Checks if the game is over.
     * @param player1 The Tetris instance for player 1.
     * @param player2 The Tetris instance for player 2.
     * @return True if the game is over, false otherwise.
     */
    bool gameOver(Tetris& player1, Tetris& player2);

    /**
     * @brief Handles the winner and game over conditions.
     * @param player1 The Tetris instance for player 1.
     * @param player2 The Tetris instance for player 2.
     * @param isGameOn Reference to a boolean indicating whether the game is still on.
     * @param isInColor Reference to a boolean indicating whether the game is in color mode.
     */
    void handleWinner(Tetris& player1, Tetris& player2, bool& isGameOn, bool& isInColor);

    /**
     * @brief Prints the game over message with the winner's number.
     * @param winnerNumber The number of the winning player.
     */
    void printGameOver(const int& winnerNumber);

public:
    /**
     * @brief Runs the Tetris game.
     */
    void run();

    /**
     * @brief Plays a single game round between two players.
     * @param player1 The Tetris instance for player 1.
     * @param player2 The Tetris instance for player 2.
     * @param isGameOn Reference to a boolean indicating whether the game is still on.
     * @param isInColor Reference to a boolean indicating whether the game is in color mode.
     */
    void playGame(Tetris& player1, Tetris& player2, bool& isGameOn, bool& isInColor);
};

#endif // GAME_H