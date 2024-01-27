#include "tetris.h"

extern HANDLE hStdOut;


Tetris::Tetris(const char* _keys, int _drawOffset, bool& isInColor): keys(_keys), currBlock(isInColor)
{  
	keyPressed = GameConfig::NO_ACTION;
	didLoose = false;
	shouldLock = false;
	drawOffset = _drawOffset * GameConfig::BOARD_DIFF;
	score = 0;
}


void Tetris::clearGame(bool& isInColor)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
		for (size_t j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			grid[i][j].ch = ' ';
			grid[i][j].color = GameConfig::BLACK;
		}

	didLoose = false;
	currBlock.reset(isInColor);
	score = 0;
}


void Tetris::nextMove(const char input, bool& isInColor)
{
	keyPressed = input;
	GameConfig::eCommands direction = getDirection();
	currBlock.draw(' ', drawOffset);
	
	currBlock.move(direction);
	if (!isValidMove(currBlock, direction))
	{
		currBlock.unMove(direction);
		//if(direction != GameConfig::eCommands::DOWN && direction != GameConfig::eCommands::DROP)
			//currBlock.move(GameConfig::eCommands::DOWN);
	}

	currBlock.draw('#', drawOffset);

	if (shouldLock)
	{
		lockBlock();	
		shouldLock = false;
		handleFullLine();
		drawBoard();
		currBlock.reset(isInColor);
	}
	else if (input == keys[(int)GameConfig::eCommands::DROP] || 
		input + GameConfig::LOWER_UPPER_DIFF == keys[(int)GameConfig::eCommands::DROP])
	{
		Sleep(10);
		nextMove(keys[(int)GameConfig::eCommands::DROP], isInColor);
	}
}


bool Tetris::isValidMove(Block& block,const GameConfig::eCommands& direction)
{
	Point points[GameConfig::BLOCK_SIZE];
	block.getPoints(points);
	return isPosValid(points, direction);
}


bool Tetris::isPosValid(Point* ptArr, const GameConfig::eCommands& direction)
{
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		if (ptArr[i].getX() == 0 || ptArr[i].getX() == GameConfig::GAME_WIDTH + 1)
			return false;

		if (grid[ptArr[i].getX() - 1][ptArr[i].getY() - 1].ch != ' ')
		{
			if (direction == GameConfig::eCommands::DOWN || direction == GameConfig::eCommands::DROP)
			{
				shouldLock = true;
			}
			return false;
		}

		if ((ptArr[i].getY() == GameConfig::GAME_HEIGHT + 1))
		{
			shouldLock = true;
			return false;
		}
	}

	return true;
}


void Tetris::lockBlock()
{
	Point points[GameConfig::BLOCK_SIZE];
	currBlock.getPoints(points);
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		grid[points[i].getX() - 1][points[i].getY() - 1].ch = '#';
		grid[points[i].getX() - 1][points[i].getY() - 1].color = currBlock.getColor();
	}
}


GameConfig::eCommands Tetris::getDirection() 
{
	for (size_t i = 0; i < GameConfig::NUM_OF_KEYS; i++)
		if ((int)keys[i] - (int)keyPressed == GameConfig::LOWER_UPPER_DIFF ||
			(int)keys[i] - (int)keyPressed == 0)
			return (GameConfig::eCommands)i;

	return GameConfig::eCommands::DOWN;
}


void Tetris::handleFullLine()
{
	int read, write;
	read = write = GameConfig::GAME_HEIGHT;
	while(read >= 0)
	{
		if (!isFullLine(read))
		{
			copyLine(read, write);
			write--;
		}
		read--;
	}

	score += ((write + 1) * (write + 1)) * GameConfig::POINTS_PER_LINE;

	while (write >= 0)
	{
		resetLine(write);
		write--;
	}
}


void Tetris::resetLine(int row)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		grid[i][row].ch = ' ';
	}
}


void Tetris::copyLine(int read, int write)
{
	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		grid[i][write] = grid[i][read];
	}
}


bool Tetris::isFullLine(int row)
{
	for (size_t col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		if (grid[col][row].ch == ' ')
			return false;
	}
	return true;
}


void Tetris::drawBoard()
{

	gotoxy(GameConfig::MIN_X + drawOffset, GameConfig::MIN_Y - 3);
	cout << "SCORE: " << score;

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::MIN_X - 1 + drawOffset, row);
		cout << '|';
		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X + drawOffset , row);
		cout << '|';
	}

	for (int col = GameConfig::MIN_X - 1 + drawOffset;
		col <= GameConfig::GAME_WIDTH + GameConfig::MIN_X + drawOffset; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << '-';
		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << '-';
	}


	for (size_t i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (size_t j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			gotoxy(i + GameConfig::MIN_X + drawOffset, j + GameConfig::MIN_Y);	
			SetConsoleTextAttribute(hStdOut, grid[i][j].color);
			cout << this->grid[i][j].ch;
		}
	}

	SetConsoleTextAttribute(hStdOut, GameConfig::WHITE);
}
