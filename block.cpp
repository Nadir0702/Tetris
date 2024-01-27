#include "block.h"
#include "tetris.h"


void Block::resetPoints()
{
	Point originPoint;
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
		points[i] = originPoint;
}


void Block::reset(bool& isInColor) 
{
	srand(time(NULL));
	shape = (GameConfig::eShapes)(rand() % GameConfig::numOfShapes);
	orientation = 0;

	resetPoints(); 
	switch (shape)
	{
	case GameConfig::eShapes::I:
		points[0].move(GameConfig::eCommands::DOWN);
		points[2] = points[0];
		points[2].move(GameConfig::eCommands::DOWN);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::DOWN);
		color = GameConfig::CYAN;
		break;
	case GameConfig::eShapes::L:
		points[0].move(GameConfig::eCommands::DOWN);
		points[2] = points[0];
		points[2].move(GameConfig::eCommands::DOWN);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::RIGHT);
		color = GameConfig::ORANGE;
		break;
	case GameConfig::eShapes::Z:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::LEFT);
		points[3] = points[1];
		points[3].move(GameConfig::eCommands::RIGHT);
		color = GameConfig::RED;
		break;
	case GameConfig::eShapes::S:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::RIGHT);
		points[3] = points[1];
		points[3].move(GameConfig::eCommands::LEFT);
		color = GameConfig::GREEN;
		break;
	case GameConfig::eShapes::PLUS:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::LEFT);
		points[3].move(GameConfig::eCommands::RIGHT);
		color = GameConfig::MAGENTA;
		break;
	case GameConfig::eShapes::SQUARE:
		points[1].move(GameConfig::eCommands::DOWN);
		points[2].move(GameConfig::eCommands::RIGHT);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::DOWN);
		color = GameConfig::YELLOW;
		break;
	case GameConfig::eShapes::REVERSEL:
		points[0].move(GameConfig::eCommands::DOWN);
		points[2] = points[0];
		points[2].move(GameConfig::eCommands::DOWN);
		points[3] = points[2];
		points[3].move(GameConfig::eCommands::LEFT);
		color = GameConfig::BLUE;
		break;
	default:
		break;
	}
	
	if (!isInColor)
		color = GameConfig::WHITE;
}


void Block::unMove(GameConfig::eCommands direction)
{
	switch (direction)
	{
	case GameConfig::eCommands::DROP:
		move(GameConfig::eCommands::UP);
		break;
	case GameConfig::eCommands::DOWN:
		move(GameConfig::eCommands::UP);
		break;
	case GameConfig::eCommands::UP:
		move(GameConfig::eCommands::DOWN);
		break;
	case GameConfig::eCommands::LEFT:
		move(GameConfig::eCommands::RIGHT);
		break;
	case GameConfig::eCommands::RIGHT:
		move(GameConfig::eCommands::LEFT);
		break;
	case GameConfig::eCommands::ROTATE_CLOCKWISE:
		move(GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE);
		break;
	case GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE:
		move(GameConfig::eCommands::ROTATE_CLOCKWISE);
		break;
	default:
		break;
	}
}


void Block::getPoints(Point* pointsArr)
{
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
	{
		pointsArr[i].setX(points[i].getX());
		pointsArr[i].setY(points[i].getY());
	}
}


void Block::draw(const char& ch, const int& drawOffset)
{
	for (size_t i = 0; i < GameConfig::BLOCK_SIZE; i++)
		points[i].draw(ch, drawOffset, color);
}


void Block::move(GameConfig::eCommands direction)
{
	if (direction == GameConfig::eCommands::ROTATE_CLOCKWISE || direction == GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE)
		rotate(direction);
	else
		for (int i = 0; i < GameConfig::BLOCK_SIZE; i++)
			points[i].move(direction);
}


void Block::rotate(GameConfig::eCommands direction)
{
	if (direction == GameConfig::eCommands::ROTATE_CLOCKWISE)
		orientation = (orientation + 1) % 4;
	if (direction == GameConfig::eCommands::ROTATE_COUNTERCLOCKWISE)
		orientation = (orientation + 3) % 4;

	switch (shape)
	{
	case GameConfig::eShapes::I:
		rotateI(direction);
		break;
	case GameConfig::eShapes::L:
		rotateL(direction);
		break;
	case GameConfig::eShapes::Z:
		rotateZ(direction);
		break;
	case GameConfig::eShapes::S:
		rotateS(direction);
		break;
	case GameConfig::eShapes::PLUS:
		rotatePlus(direction);
		break;
	case GameConfig::eShapes::REVERSEL:
		rotateReverseL(direction);
		break;
	default:
		break;
	}
}


void Block::rotatePlus(GameConfig::eCommands direction)
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY());
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY());
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() - 1);
		break;
	default:
		break;
	}
}


void Block::rotateI(GameConfig::eCommands direction)
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() + 2);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 2);
		points[3].setY(points[0].getY());
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX());
		points[3].setY(points[0].getY() - 2);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 2);
		points[3].setY(points[0].getY());
		break;
	default:
		break;
	}
}


void Block::rotateL(GameConfig::eCommands direction)
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	default:
		break;
	}
}


void Block::rotateS(GameConfig::eCommands direction)
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	default:
		break;
	}
}


void Block::rotateZ(GameConfig::eCommands direction)
{
		switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	default:
		break;
	}
}


void Block::rotateReverseL(GameConfig::eCommands direction)
{
	switch (orientation)
	{
	case(ORIENTATIONS[0]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() - 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() + 1);
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() + 1);
		break;
	case(ORIENTATIONS[1]):
		points[1].setX(points[0].getX() + 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() - 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() - 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[2]):
		points[1].setX(points[0].getX());
		points[1].setY(points[0].getY() + 1);
		points[2].setX(points[0].getX());
		points[2].setY(points[0].getY() - 1);
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() - 1);
		break;
	case(ORIENTATIONS[3]):
		points[1].setX(points[0].getX() - 1);
		points[1].setY(points[0].getY());
		points[2].setX(points[0].getX() + 1);
		points[2].setY(points[0].getY());
		points[3].setX(points[0].getX() + 1);
		points[3].setY(points[0].getY() + 1);
		break;
	default:
		break;
	}
}
