#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Space.h"


#include <iostream>

std::vector<std::vector<Space>> createBoard(int board_size, sf::RenderWindow& window);
void emptyBoard(std::vector<std::vector<Space>> &board, sf::RenderWindow& window);
void add_mines(std::vector<std::vector<Space>>& board, int num_of_mines);
void update_numbers(std::vector<std::vector<Space>>& board);
void checkForBlanks(std::vector<std::vector<Space>> &board, int x, int y, bool bypass = false);
void showMines(std::vector<std::vector<Space>>& board);