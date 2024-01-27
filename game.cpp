#include "game.h"


void Game::run()
{
	Menu menu;
	Tetris player1(GameConfig::keysP1, 0, menu.getIsInColor()), player2(GameConfig::keysP2, 1, menu.getIsInColor());
	
	while (!menu.getIsExit())
		menu.chooseOption(player1, player2, *this);

}


void Game::playGame(Tetris& player1, Tetris& player2, bool& isGameOn,bool& isInColor)
{
	player1.drawBoard();
	player2.drawBoard();

	while (!gameOver(player1, player2))
	{
		char input = GameConfig::NO_ACTION;
		if (_kbhit())
		{
			input = _getch();
			if (input == GameConfig::ESC)
				return;	
		}

		player1.nextMove(input, isInColor);
		player2.nextMove(input, isInColor);

		Sleep(500);
	}

	handleWinner(player1, player2, isGameOn, isInColor); //TODO
}


void Game::handleWinner(Tetris& player1, Tetris& player2, bool& isGameOn, bool& isInColor)
{
	int winner = 3;

	if (player1.getDidLoose())
		winner -= 1;
	if (player2.getDidLoose())
		winner -= 2;

	if (!winner)
	{
		if (player1.getScore() < player2.getScore())
			winner = 2;
		else if (player1.getScore() > player2.getScore())
			winner = 1;
	}

	printGameOver(winner);

	isGameOn = false;
	isInColor = false;
}


void Game::printGameOver(const int& winnerNumber)
{
	int printY = GameConfig::MIN_Y + GameConfig::GAME_HEIGHT / 2 - 5;
	int printX = GameConfig::MIN_X + GameConfig::BOARD_DIFF / 2;

	gotoxy(printX, printY);
	cout << "\033[1;31mGAME OVER!\033[0m";
	printY += 2;

	if (winnerNumber)
	{
		gotoxy(printX - 2, printY);
		cout << "\033[1;32mPLAYER " << winnerNumber << " WIN!!!\033[0m";
	}
	else
	{
		gotoxy(printX - 2, printY);
		cout << "\033[1;34mIT'S A DRAW....\033[0m";
	}
	
	gotoxy(printX - 8, GameConfig::MIN_Y + GameConfig::GAME_HEIGHT - 5);
	cout << "Press any key to continue...";
	_getch();
}


bool Game::gameOver(Tetris& player1, Tetris& player2)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		if (player1.grid[i][0].ch != ' ') 
			player1.setDidLoose(true);
		if (player2.grid[i][0].ch != ' ')
			player2.setDidLoose(true);
	}

	return player1.getDidLoose() || player2.getDidLoose();
}
