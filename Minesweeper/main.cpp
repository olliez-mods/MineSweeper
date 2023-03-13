#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Space.h"
#include "Resources.h"
#include "resourcePath/RpFinder.hpp"

#include <iostream>

int main()
{
    const int BOARD_SIZE = 16;
    const int SIZE_PER_SQUARE = 20;
    const int NUM_OF_MINES = 50;

    bool firstclick = true;
    bool canRightClick = true;
    bool canLeftClick = true;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(BOARD_SIZE * SIZE_PER_SQUARE, BOARD_SIZE * SIZE_PER_SQUARE)), "MineSweeper", sf::Style::Titlebar | sf::Style::Close);

    std::vector<std::vector<Space>> board;
    std::vector<std::vector<Space>> empty_board;
    
    board = createBoard(BOARD_SIZE, window);
    add_mines(board, NUM_OF_MINES);
    update_numbers(board);

    sf::Image icon;
    icon.loadFromFile(sfas::rp() + "sprites/icon.png"); // File/Image/Pixel
    window.setIcon(sf::Vector2u(icon.getSize().x, icon.getSize().y), icon.getPixelsPtr());

    sf::RectangleShape backround_rect = sf::RectangleShape(sf::Vector2f(BOARD_SIZE * SIZE_PER_SQUARE, BOARD_SIZE * SIZE_PER_SQUARE));
    backround_rect.setFillColor(sf::Color(130, 130, 130));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        if (Space::howManyFlagged() >= NUM_OF_MINES)
        {
            bool ok_go_on = true;
            for (int x = 0; x < board.size(); x++)
            {
                for (int y = 0; y < board.size(); y++)
                {
                    if ((board[x][y].isFlagged() && !board[x][y].isMine()) || (!board[x][y].isMine() && board[x][y].isHidden()))
                    {
                        ok_go_on = false;
                    }
                }
            }
            if (ok_go_on)
            {
                emptyBoard(board, window);
                firstclick = true;
            }
        }
        window.setTitle("MineSweeper: " + std::to_string(NUM_OF_MINES - Space::howManyFlagged()));
        if (sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < board.size() * SIZE_PER_SQUARE &&
            sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < board.size() * SIZE_PER_SQUARE)
        {

            //Mouse press left starts here...
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (canLeftClick)
                {
                    //get the mouse pos, and use that to get what tile the mouse is over
                    sf::Vector2i mos_pos = sf::Mouse::getPosition(window);
                    sf::Vector2i board_pos = sf::Vector2i(std::floor(mos_pos.x / SIZE_PER_SQUARE), std::floor(mos_pos.y / SIZE_PER_SQUARE));


                    if (firstclick)
                    {
                        Space::resetFlagCount();
                        do
                        {

                            emptyBoard(board, window);
                            add_mines(board, NUM_OF_MINES);
                            update_numbers(board);
                            firstclick = false;
                            board[board_pos.x][board_pos.y].show();
                            checkForBlanks(board, board_pos.x, board_pos.y, true);

                        } while (board[board_pos.x][board_pos.y].getMinesAround() == -1);

                    }
                    else  if (!board[board_pos.x][board_pos.y].isFlagged()) {

                        if (board[board_pos.x][board_pos.y].isMine())
                        {
                            showMines(board);
                            board[board_pos.x][board_pos.y].show(1);
                            firstclick = true;
                        }
                        else
                        {
                            board[board_pos.x][board_pos.y].show();
                            checkForBlanks(board, board_pos.x, board_pos.y);
                        } 
                    }
                }
                canLeftClick = false;
            }
            else
            {
                canLeftClick = true;
            }
            //ends here


            //Mouse press right starts here...
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (canRightClick)
                {
                    sf::Vector2i mos_pos = sf::Mouse::getPosition(window);
                    sf::Vector2i board_pos = sf::Vector2i(std::floor(mos_pos.x / SIZE_PER_SQUARE), std::floor(mos_pos.y / SIZE_PER_SQUARE));
                    if (!board[board_pos.x][board_pos.y].isFlagged() && board[board_pos.x][board_pos.y].isHidden())
                    {
                        board[board_pos.x][board_pos.y].flag();
                    }
                    else if(board[board_pos.x][board_pos.y].isFlagged() && board[board_pos.x][board_pos.y].isHidden())
                    {
                        board[board_pos.x][board_pos.y].unflag();
                    }
                }
                canRightClick = false;
            } else
            {
                canRightClick = true;
            }
        }
        //ends here

        //draw each tile to the screen
        window.draw(backround_rect);
        for (int x = 0; x < board.size(); x++)
        {
            for (int y = 0; y < board.size(); y++)
            {
                sf::RectangleShape temp = board[x][y].getRect();
                window.draw(temp);
            }
        }

        window.display();
    }

    return 0;
}
