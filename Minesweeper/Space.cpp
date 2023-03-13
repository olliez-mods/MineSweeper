#include "Space.h"
#include "resourcePath/RpFinder.hpp"

int Space::howManyIsFlagged = 0;
void Space::show(int type)
{
	hidden = false;
	if (type == 1)
	{
		texture.loadFromFile(sfas::rp() + "sprites/red_mine.png");
	}
	else if (type == 2)
	{
		texture.loadFromFile(sfas::rp() + "sprites/flagged_mine.png");
	}
	else if (type == 3)
	{
		texture.loadFromFile(sfas::rp() + "sprites/red_flag.png");
	}
	else if (mine)
	{
		texture.loadFromFile(sfas::rp() + "sprites/mine.png");
	}else
	{
		texture.loadFromFile(sfas::rp() + "sprites/" + std::to_string(mines_around) + ".png");
	}
	rect.setTexture(&texture);
}

void Space::unflag()
{
	howManyIsFlagged--;
	flagged = false;
	texture.loadFromFile(sfas::rp() + "sprites/hidden.png");
	rect.setTexture(&texture);
}

void Space::flag()
{
	howManyIsFlagged++;
	flagged = true;
	texture.loadFromFile(sfas::rp() + "sprites/flag.png");
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
