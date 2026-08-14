#include <ncurses.h>
#include <cstdlib>
#include "shape.h"
#include "Ishape.h"

Ishape::Ishape()
{
    this->shapeY = 1;
    this->shapeX = 3;
    this->rotation = 0;

    getmaxyx(stdscr, endY, endX);
    startY = (endY - ROWS) / 2;
    startX = (endX - COLS) / 2;

    insertShape('#');
    refresh();
}

Ishape::~Ishape() {}

void Ishape::insertShape(char ch)
{
    int i;

    attron(COLOR_PAIR(2));
    if (rotation == 0)
    {
        for (i = 0; i < 4; ++i)
        {
            mvaddch(startY + shapeY + 1, startX + shapeX + i + 1, ch);
        }
    }
    else if (rotation == 1)
    {
        for (i = 0; i < 4; ++i)
        {
            mvaddch(startY + shapeY + i, startX + shapeX + 3, ch);
        }
    }
    else if (rotation == 2)
    {
        for (i = 0; i < 4; ++i)
        {
            mvaddch(startY + shapeY + 2, startX + shapeX + i + 1, ch);
        }
    }
    else if (rotation == 3)
    {
        for (i = 0; i < 4; ++i)
        {
            mvaddch(startY + shapeY + i, startX + shapeX + 2, ch);
        }
    }
    attroff(COLOR_PAIR(2));
    refresh();
}

void Ishape::rotate(int gameMap[19][10])
{
    if (rotation == 0 && shapeY < 16)
    {
        if (gameMap[shapeY - 1][shapeX + 2] == 0 && gameMap[shapeY][shapeX + 2] == 0 && gameMap[shapeY + 1][shapeX + 2] == 0 && gameMap[shapeY + 2][shapeX + 2] == 0)
        {
            insertShape(' ');
            ++rotation;
            insertShape('#');
        }
    }
    else if (rotation == 1 && shapeX > -1 && shapeX < 7)
    {
        if (gameMap[shapeY + 2][shapeX] == 0 && gameMap[shapeY + 2][shapeX + 1] == 0 && gameMap[shapeY + 2][shapeX + 2] == 0 && gameMap[shapeY + 2][shapeX + 3] == 0)
        {
            insertShape(' ');
            ++rotation;
            insertShape('#');
        }
    }
    else if (rotation == 2 && shapeY < 16)
    {
        if (gameMap[shapeY][shapeX + 1] == 0 && gameMap[shapeY + 1][shapeX + 1] == 0 && gameMap[shapeY + 2][shapeX + 1] == 0 && gameMap[shapeY + 3][shapeX + 1] == 0)
        {
            insertShape(' ');
            ++rotation;
            insertShape('#');
        }
    }
    else if (rotation == 3 && shapeX > -1 && shapeX < 7)
    {
        if (gameMap[shapeY][shapeX] == 0 && gameMap[shapeY][shapeX + 1] == 0 && gameMap[shapeY][shapeX + 2] == 0 && gameMap[shapeY][shapeX + 3] == 0)
        {
            insertShape(' ');
            rotation = 0;
            insertShape('#');
        }
    }
}

int Ishape::lowerShape(int gameMap[19][10])
{
    int counter = 0;
    if (rotation == 0 && (gameMap[shapeY + 1][shapeX] != 0 || gameMap[shapeY + 1][shapeX + 1] != 0 || gameMap[shapeY + 1][shapeX + 2] != 0 || gameMap[shapeY + 1][shapeX + 3] != 0 || shapeY + 1 >= 19))
    {
        gameMap[shapeY][shapeX] = 2;
        gameMap[shapeY][shapeX + 1] = 2;
        gameMap[shapeY][shapeX + 2] = 2;
        gameMap[shapeY][shapeX + 3] = 2;

        ++counter;
    }
    else if (rotation == 1 && (gameMap[shapeY + 3][shapeX + 2] != 0 || shapeY + 3 >= 19))
    {
        gameMap[shapeY - 1][shapeX + 2] = 2;
        gameMap[shapeY][shapeX + 2] = 2;
        gameMap[shapeY + 1][shapeX + 2] = 2;
        gameMap[shapeY + 2][shapeX + 2] = 2;

        ++counter;
    }
    else if (rotation == 2 && (gameMap[shapeY + 2][shapeX] != 0 || gameMap[shapeY + 2][shapeX + 1] != 0 || gameMap[shapeY + 2][shapeX + 2] != 0 || gameMap[shapeY + 2][shapeX + 3] != 0 || shapeY + 2 >= 19))
    {
        gameMap[shapeY + 1][shapeX] = 2;
        gameMap[shapeY + 1][shapeX + 1] = 2;
        gameMap[shapeY + 1][shapeX + 2] = 2;
        gameMap[shapeY + 1][shapeX + 3] = 2;

        ++counter;
    }
    else if (rotation == 3 && (gameMap[shapeY + 3][shapeX + 1] != 0 || shapeY + 3 >= 19))
    {
        gameMap[shapeY - 1][shapeX + 1] = 2;
        gameMap[shapeY][shapeX + 1] = 2;
        gameMap[shapeY + 1][shapeX + 1] = 2;
        gameMap[shapeY + 2][shapeX + 1] = 2;

        ++counter;
    }

    if (shapeY == 0 && counter > 0)
    {
        mvaddstr(startY + 6, startX - 13, "Game over! Press any key to continue");
        nodelay(stdscr, false);
        refresh();
        getch();
        endwin();
        exit(0);
    }
    else if (counter > 0)
    {
        return 1;
    }

    insertShape(' ');
    ++shapeY;
    insertShape('#');

    return 0;
}

void Ishape::moveLeft(int gameMap[19][10])
{
    if (rotation == 0 && shapeX > 0 && gameMap[shapeY][shapeX - 1] == 0)
    {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    }
    else if (rotation == 1 && shapeX >= -1 && gameMap[shapeY - 1][shapeX + 1] == 0 && gameMap[shapeY][shapeX + 1] == 0 && gameMap[shapeY + 1][shapeX + 1] == 0 && gameMap[shapeY + 2][shapeX + 1] == 0)
    {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    }
    else if (rotation == 2 && shapeX > 0 && gameMap[shapeY + 1][shapeX - 1] == 0)
    {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    }
    else if (rotation == 3 && shapeX >= 0 && gameMap[shapeY - 1][shapeX] == 0 && gameMap[shapeY][shapeX] == 0 && gameMap[shapeY + 1][shapeX] == 0 && gameMap[shapeY + 2][shapeX] == 0)
    {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    }
}

void Ishape::moveRight(int gameMap[19][10])
{
    if (rotation == 0 && shapeX < 6 && gameMap[shapeY][shapeX + 4] == 0)
    {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    }
    else if (rotation == 1 && shapeX <= 6 && gameMap[shapeY - 1][shapeX + 3] == 0 && gameMap[shapeY][shapeX + 3] == 0 && gameMap[shapeY + 1][shapeX + 3] == 0 && gameMap[shapeY + 2][shapeX + 3] == 0)
    {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    }
    else if (rotation == 2 && shapeX < 6 && gameMap[shapeY + 1][shapeX + 4] == 0)
    {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    }
    else if (rotation == 3 && shapeX <= 7 && gameMap[shapeY - 1][shapeX + 2] == 0 && gameMap[shapeY][shapeX + 2] == 0 && gameMap[shapeY + 1][shapeX + 2] == 0 && gameMap[shapeY + 2][shapeX + 2] == 0)
    {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    }
}