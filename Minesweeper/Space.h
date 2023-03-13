#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Space
{
	bool mine = false;
	int mines_around = 0;
	bool hidden = true;
	bool flagged = false;

public:  
	bool checked = false;
	sf::Texture texture;
	sf::RectangleShape rect;


	void unflag();
	void flag();
	bool isFlagged();

	void show(int type = 0);
	bool isHidden();

	void setRect(sf::RectangleShape rect);
	sf::RectangleShape& getRect();
	void setMinesAround(int num);
	void makeMine();
	bool isMine();
	int getMinesAround();


static int howManyIsFlagged;

public:
	static int howManyFlagged();
	static void resetFlagCount();
};
