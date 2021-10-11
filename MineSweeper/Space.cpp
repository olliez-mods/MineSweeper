#include "Space.h"

int Space::howManyIsFlagged = 0;
void Space::show(int type)
{
	hidden = false;
	if (type == 1)
	{
		texture.loadFromFile("sprites/red_mine.png");
	}
	else if (type == 2)
	{
		texture.loadFromFile("sprites/flagged_mine.png");
	}
	else if (type == 3)
	{
		texture.loadFromFile("sprites/red_flag.png");
	}
	else if (mine)
	{
		texture.loadFromFile("sprites/mine.png");
	}else
	{
		texture.loadFromFile("sprites/" + std::to_string(mines_around) + ".png");
	}
	rect.setTexture(&texture);
}

void Space::unflag()
{
	howManyIsFlagged--;
	flagged = false;
	texture.loadFromFile("sprites/hidden.png");
	rect.setTexture(&texture);
}

void Space::flag()
{
	howManyIsFlagged++;
	flagged = true;
	texture.loadFromFile("sprites/flag.png");
	rect.setTexture(&texture);
}

bool Space::isFlagged()
{
	return flagged;
}

bool Space::isHidden()
{
	return hidden;
}

void Space::setRect(sf::RectangleShape rect)
{
	this->rect = rect;
}

sf::RectangleShape& Space::getRect()
{
	return rect;
}

void Space::setMinesAround(int num)
{
	mines_around = num;
}

void Space::makeMine()
{
	mine = true;
}

bool Space::isMine()
{
	return mine;
}

int Space::getMinesAround()
{
	return mines_around;
}

int Space::howManyFlagged()
{
	return howManyIsFlagged;
}

void Space::resetFlagCount()
{
	howManyIsFlagged = 0;
}
