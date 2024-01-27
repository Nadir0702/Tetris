#ifndef MENU_H
#define MENU_H

#include "io_utils.h"

 // Forward declarations
class Tetris;
class Game;

/**
 * @class Menu
 * @brief Manages the game menu and user choices.
 */
class Menu
{
private:
    // Enumeration for menu options
    enum class eOptions { START = '1', CONTINUE = '2', INSTRUCTION = '8', EXIT = '9' };

    // Constants for menu and instructions positions
    static constexpr int MENU_X = 35;
    static constexpr int MENU_Y = 8;
    static constexpr int INSTRUCTIONS_X = 25;
    static constexpr int INSTRUCTIONS_Y = 6;

    bool isGameOn;     ///< Flag indicating whether the game is ongoing.
    bool isExit;       ///< Flag indicating whether the user chose to exit.
    bool isInColor;    ///< Flag indicating whether the game is in color mode.

    Menu::eOptions input;  ///< User input for menu choices.

    /**
     * @brief Prints the main menu options.
     */
    void printMenu();

    /**
     * @brief Prints game instructions.
     */
    void printInstructions();

    /**
     * @brief Loads the game with player instances and starts the game loop.
     * @param player1 The Tetris instance for player 1.
     * @param player2 The Tetris instance for player 2.
     * @param game The Game instance for managing the game flow.
     */
    void loadGame(Tetris& player1, Tetris& player2, Game& game);

    /**
     * @brief Prints the exit message.
     */
    void printExit();

    /**
     * @brief Prompts the user to choose color mode for the game.
     */
    void chooseColors();

public:
    /**
     * @brief Constructor for the Menu class.
     * Initializes flags and menu input.
     */
    Menu() : isExit(false), isGameOn(false), input(static_cast<Menu::eOptions>(0)), isInColor(false) {}

    /**
     * @brief Gets the value of the exit flag.
     * @return True if the user chose to exit, false otherwise.
     */
    bool getIsExit() { return isExit; }

    /**
     * @brief Gets the reference to the isInColor flag.
     * @return Reference to the flag indicating whether the game is in color mode.
     */
    bool& getIsInColor() { return isInColor; }

    /**
     * @brief Handles user's menu choice and initiates corresponding actions.
     * @param player1 The Tetris instance for player 1.
     * @param player2 The Tetris instance for player 2.
     * @param game The Game instance for managing the game flow.
     */
    void chooseOption(Tetris& player1, Tetris& player2, Game& game);
};

#endif // !MENU_H