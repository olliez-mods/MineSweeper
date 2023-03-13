#include "Resources.h"
#include "resourcePath/RpFinder.hpp"

std::vector<sf::Vector2i> checked = std::vector<sf::Vector2i>();

bool is_valid(int x, int y, std::vector<std::vector<Space>> &board)
{
	if (x >= 0 && y >= 0 && x < board.size() && y < board.size())
	{
	return true;
	}
	return false;
}

std::vector<std::vector<Space>> createBoard(int board_size, sf::RenderWindow& window)
{
	std::vector<std::vector<Space>> board;
	for (int x = 0; x < board_size; x++)
	{
		board.push_back(std::vector<Space>());
		for (int y = 0; y < board_size; y++)
		{
			board[x].push_back(Space());
			sf::RectangleShape new_rect = sf::RectangleShape(sf::Vector2f(window.getSize().x / board_size, window.getSize().y / board_size));
			new_rect.setPosition(sf::Vector2f(x * (window.getSize().x / board_size), y * (window.getSize().y / board_size)));
			board[x][y].setRect(new_rect);

		}
	}
	
	return board;
}

void emptyBoard(std::vector<std::vector<Space>> &board, sf::RenderWindow& window)
{
	for (int x = 0; x < board.size(); x++)
	{
		for (int y = 0; y < board.size(); y++)
		{
			board[x][y] = Space();
			sf::RectangleShape new_rect = sf::RectangleShape(sf::Vector2f(window.getSize().x / board.size(), window.getSize().y / board.size()));
			new_rect.setPosition(sf::Vector2f(x * (window.getSize().x / board.size()), y * (window.getSize().y / board.size())));
			board[x][y].setRect(new_rect);
			board[x][y].texture.loadFromFile(sfas::rp() + "sprites/hidden.png");
			board[x][y].rect.setTexture(&board[x][y].texture);
		}
	}
}

void add_mines(std::vector<std::vector<Space>>& board, int num_of_mines)
{
	srand(time(0));
	for (int i = 0; i < num_of_mines; i++)
	{
		int x_rand;
		int y_rand;
		bool contin = true;

		while (contin)
		{
			x_rand = rand() % board.size();
			y_rand = rand() % board.size();
			if (!board[x_rand][y_rand].isMine())
			{
				contin = false;
			}
		}
		board[x_rand][y_rand].makeMine();
		//board[x_rand][y_rand].rect.setFillColor(sf::Color::Red);
	}
}

void update_numbers(std::vector<std::vector<Space>>& board)
{
	for (int x = 0; x < board.size(); x++)
	{
		for (int y = 0; y < board.size(); y++)
		{
			int num_of_mines_around = 0;
			if (is_valid(x - 1, y - 1, board) && board[x - 1][y - 1].isMine()) { num_of_mines_around++; }
			if (is_valid(x, y - 1, board) && board[x][y - 1].isMine()) { num_of_mines_around++; }
			if (is_valid(x + 1, y - 1, board) && board[x + 1][y - 1].isMine()) { num_of_mines_around++; }
			if (is_valid(x - 1, y, board) && board[x - 1][y].isMine()) { num_of_mines_around++; }
			if (is_valid(x + 1, y, board) && board[x + 1][y].isMine()) { num_of_mines_around++; }
			if (is_valid(x - 1, y + 1, board) && board[x - 1][y + 1].isMine()) { num_of_mines_around++; }
			if (is_valid(x, y + 1, board) && board[x][y + 1].isMine()) { num_of_mines_around++; }
			if (is_valid(x + 1, y + 1, board) && board[x + 1][y + 1].isMine()) { num_of_mines_around++; }

			board[x][y].setMinesAround(num_of_mines_around);
			if (board[x][y].isMine())
			{
				board[x][y].setMinesAround(-1);
			}

			board[x][y].texture.loadFromFile(sfas::rp() + "sprites/hidden.png");
			board[x][y].rect.setTexture(&board[x][y].texture);
		}
	}
}

void checkForBlanks(std::vector<std::vector<Space>> &board, int x, int y, bool bypass)
{
	if (!bypass)
	{
		if (board[x][y].getMinesAround() != 0 || board[x][y].checked)
		{
			return;
		}
	}

	board[x][y].checked = true;

	if (is_valid(x - 1, y - 1, board) && board[x - 1][y - 1].getMinesAround() >= 0)
	{
		board[x - 1][y - 1].show();
		checkForBlanks(board, x - 1, y - 1);
	}

	if (is_valid(x, y - 1, board) && board[x][y - 1].getMinesAround() >= 0) {
		board[x][y - 1].show();
		checkForBlanks(board, x, y - 1);
	}

	if (is_valid(x + 1, y - 1, board) && board[x + 1][y - 1].getMinesAround() >= 0) {
		board[x + 1][y - 1].show();
		checkForBlanks(board, x + 1, y - 1);
	}

	if (is_valid(x - 1, y, board) && board[x - 1][y].getMinesAround() >= 0) {
		board[x - 1][y].show();
		checkForBlanks(board, x - 1, y);
	}

	if (is_valid(x + 1, y, board) && board[x + 1][y].getMinesAround() >= 0) {
		board[x + 1][y].show();
		checkForBlanks(board, x + 1, y);
	}

	if (is_valid(x - 1, y + 1, board) && board[x - 1][y + 1].getMinesAround() >= 0) {
		board[x - 1][y + 1].show();
		checkForBlanks(board, x - 1, y + 1);
	}

	if (is_valid(x, y + 1, board) && board[x][y + 1].getMinesAround() >= 0) {
		board[x][y + 1].show();
		checkForBlanks(board, x, y + 1);
	}

	if (is_valid(x + 1, y + 1, board) && board[x + 1][y + 1].getMinesAround() >= 0) {
		board[x + 1][y + 1].show();
		checkForBlanks(board, x + 1, y + 1);
	}
}

void showMines(std::vector<std::vector<Space>>& board)
{
	for (int x = 0; x < board.size(); x++)
	{
		for (int y = 0; y < board.size(); y++)
		{
			if (board[x][y].isMine())
			{
				if (board[x][y].isFlagged())
				{
					board[x][y].show(2);
				}
				else
				{
					board[x][y].show();
				}
			}
			else if (board[x][y].isFlagged() && !board[x][y].isMine())
			{
				board[x][y].show(3);
			}
		}
	}
}
