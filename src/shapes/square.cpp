#include <ncurses.h>
#include <cstdlib>
#include "shape.h"
#include "square.h"

square::square()
{
    this->shapeY = 0;
    this->shapeX = 4;

    getmaxyx(stdscr, endY, endX);
    startY = (endY - ROWS) / 2;
    startX = (endX - COLS) / 2;

    insertShape('#');
    refresh();
}

square::~square() {}

void square::insertShape(char ch)
{
    int i, j;

    attron(COLOR_PAIR(1));
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            mvaddch(startY + shapeY + i + 1, startX + shapeX + j + 1, ch);
        }
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

void square::rotate(int gameMap[19][10]) {}

int square::lowerShape(int gameMap[19][10])
{
    if (shapeY + 2 >= 19 || gameMap[shapeY + 2][shapeX] != 0 || gameMap[shapeY + 2][shapeX + 1] != 0)
    {
        gameMap[shapeY][shapeX] = 1;
        gameMap[shapeY][shapeX + 1] = 1;
        gameMap[shapeY + 1][shapeX] = 1;
        gameMap[shapeY + 1][shapeX + 1] = 1;

        if (shapeY == 0)
        {
            mvaddstr(startY + 6, startX - 13, "Game over! Press any key to continue");
            nodelay(stdscr, false);
            refresh();
            getch();
            endwin();
            exit(0);
        }

        return 1;
    }
    insertShape(' ');
    ++shapeY;
    insertShape('#');

    return 0;
}

void square::moveLeft(int gameMap[19][10])
{
    if (shapeX > 0 && gameMap[shapeY][shapeX - 1] == 0 && gameMap[shapeY + 1][shapeX - 1] == 0)
    {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    }
}

void square::moveRight(int gameMap[19][10])
{
    if (shapeX + 2 < 10 && gameMap[shapeY][shapeX + 2] == 0 && gameMap[shapeY + 1][shapeX + 2] == 0)
    {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    }
}