#include "menu.h"
#include "tetris.h"
#include "game.h"


void Menu::chooseOption(Tetris& player1, Tetris& player2, Game& game)
{
	printMenu();
	input = (Menu::eOptions)_getch();

	switch (input)
	{
	case Menu::eOptions::START:
		chooseColors();
		isGameOn = true;		
		player1.clearGame(isInColor);
		player2.clearGame(isInColor);
		loadGame(player1, player2, game);
		break;
	case Menu::eOptions::CONTINUE:
		if(isGameOn)
			loadGame(player1, player2, game);
		break;
	case Menu::eOptions::INSTRUCTION:
		clear_screen();
		printInstructions();
		break;
	case Menu::eOptions::EXIT:
		clear_screen();
		printExit();
		isExit = true;
		return;
		break;
	default:
		break;
	}

	clear_screen();
}


void Menu::chooseColors()
{
	int nemu_y = MENU_Y;
	char answer = 0;
	bool isValidInput = false;

	while (!isValidInput)
	{
		clear_screen();
		gotoxy(MENU_X, nemu_y);
		cout << "Would you like to play with Colors?";
		nemu_y += 2;

		gotoxy(MENU_X, nemu_y);
		cout << "	Y	/	N";
		
		answer = _getch();

		if (answer == 'y' || answer == 'Y') 
		{
			isInColor = true;
			isValidInput = true;
		}
			
		if (answer == 'n' || answer == 'N')
		{
			isInColor = false;
			isValidInput = true;
		}

		nemu_y = MENU_Y;
	}
	
	answer = 0;

	clear_screen();
}


void Menu::loadGame(Tetris& player1, Tetris& player2, Game& game) 
{
	clear_screen();
	game.playGame(player1, player2, isGameOn, isInColor);
}


void Menu::printExit()
{
	gotoxy(MENU_X, MENU_Y);
	cout << "  *********************************" << std::endl;
	gotoxy(MENU_X, MENU_Y + 1);
	cout << "  * \033[1;31mTHANK\033[0m \033[1;32mYOU\033[0m \033[1;33mFOR\033[0m \033[1;34mPLAYING\033[0m \033[1;35mTETRIS!\033[0m *" << std::endl;
	gotoxy(MENU_X, MENU_Y + 2);
	cout << "  *********************************" << std::endl;
}


void Menu::printMenu()
{
	int nemu_y = MENU_Y;

	gotoxy(MENU_X, nemu_y);
	cout << "(" << (char)Menu::eOptions::START << ") Start a new game" << endl;
	nemu_y++;

	if (isGameOn)
	{
		gotoxy(MENU_X, nemu_y);
		cout << "(" << (char)Menu::eOptions::CONTINUE << ") Continue a paused game" << endl;
		nemu_y++;
	}

	gotoxy(MENU_X, nemu_y);
	cout << "(" << (char)Menu::eOptions::INSTRUCTION << ") Present instructions and keys" << endl;
	nemu_y++;

	gotoxy(MENU_X, nemu_y);
	cout << "(" << (char)Menu::eOptions::EXIT << ") EXIT" << endl;
}


void Menu::printInstructions()
{
	char keyPressed = 0;
	int instructions_y = INSTRUCTIONS_Y;

	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "In Tetris, your objective is to manipulate falling tetrominoes " << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "composed of four blocks each, to create solid horizontal lines " << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "at the bottom of the playing field." << endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "COMMAND\\KEY			PLYAER 1		PLAYER 2" << endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "LEFT				a / A			j / J" << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "RIGHT				d / D			l / L" << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "ROTATE clockwise		s / S			k / K" << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "ROTATE counterclockwise	w / W			i / I" << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "DROP				x / X			m / M" << endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "Clearing lines earns  points. Plan your moves strategically to avoid creating " << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "gaps in the stack, and aim for Tetrises(clearing four lines at once) " << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "The game ends if the stack reaches the top of the screen " << endl;
	instructions_y++;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "Enjoy the timeless puzzle - solving challenge of Tetris!" << endl;
	instructions_y += 2;
	gotoxy(INSTRUCTIONS_X, instructions_y);
	cout << "Press ESC to go back to the Menu" << endl;


	while(keyPressed != GameConfig::ESC)
		if(_kbhit())
			keyPressed = _getch();

}