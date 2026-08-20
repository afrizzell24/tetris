#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "square.h"
#include "shape.h"
#include "Ishape.h"
#include "Tshape.h"
#include "Lshape.h"

using namespace std;

#define ROWS 21
#define COLS 12

int startY, startX;
char gameBorder[21][12];
int gameMap[19][10];

void initializeBorder()
{
    int i, j, endY, endX;

    getmaxyx(stdscr, endY, endX);
    startY = (endY - ROWS) / 2;
    startX = (endX - COLS) / 2;

    for (i = 0; i < 21; ++i)
    {
        for (j = 0; j < 12; ++j)
        {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                gameBorder[i][j] = '#';
            }
            else
            {
                gameBorder[i][j] = ' ';
            }

            mvaddch(startY + i, startX + j, gameBorder[i][j]);
        }
    }
    refresh();
}

void initializeGameMap()
{
    int i, j;
    for (i = 0; i < 19; ++i)
    {
        for (j = 0; j < 10; ++j)
        {
            gameMap[i][j] = 0;
        }
    }
}

void forTesting()
{
    int i, j;
    for (i = 0; i < 19; ++i)
    {
        for (j = 0; j < 10; ++j)
        {
            mvprintw(startY + i + 1, startX + j - 20, "%d", gameMap[i][j]);
        }
    }
    refresh();
}

void checkRows()
{
    int i, j, k, l, counter;

    for (i = 18; i >= 0; --i)
    {
        counter = 0;
        for (j = 0; j < 10; ++j)
        {
            if (gameMap[i][j] != 0)
            {
                ++counter;
            }
        }

        if (counter == 10)
        {
            for (k = i; k > 0; --k)
            {
                for (l = 0; l < 10; ++l)
                {
                    gameMap[k][l] = gameMap[k - 1][l];
                }
            }
            for (k = 0; k < 19; ++k)
            {
                for (l = 0; l < 10; ++l)
                {
                    if (gameMap[k][l] == 1)
                    {
                        attron(COLOR_PAIR(1));
                        mvaddch(startY + k + 1, startX + l + 1, '#');
                        attroff(COLOR_PAIR(1));
                    }
                    else if (gameMap[k][l] == 2)
                    {
                        attron(COLOR_PAIR(2));
                        mvaddch(startY + k + 1, startX + l + 1, '#');
                        attroff(COLOR_PAIR(2));
                    }
                    else if (gameMap[k][l] == 3)
                    {
                        attron(COLOR_PAIR(3));
                        mvaddch(startY + k + 1, startX + l + 1, '#');
                        attroff(COLOR_PAIR(3));
                    }
                    else if (gameMap[k][l] == 4)
                    {
                        attron(COLOR_PAIR(4));
                        mvaddch(startY + k + 1, startX + l + 1, '#');
                        attroff(COLOR_PAIR(4));
                    }
                    else
                    {
                        mvaddch(startY + k + 1, startX + l + 1, ' ');
                    }
                }
            }
            refresh();
            usleep(500000);
            ++i;
        }
    }

    refresh();
}

void setPiece(Shape *&tmp)
{
    int selectPiece = rand() % 4;
    if (selectPiece == 0)
    {
        tmp = new square();
    }
    else if (selectPiece == 1)
    {
        tmp = new Ishape();
    }
    else if (selectPiece == 2)
    {
        tmp = new Tshape();
    }
    else if (selectPiece == 3)
    {
        tmp = new Lshape();
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    cbreak();

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    initializeBorder();
    initializeGameMap();

    Shape *tmp = nullptr;
    setPiece(tmp);

    int userInput = -1;
    int usleepDelay = 10000;
    int dropShape = 0;
    while (1)
    {
        userInput = getch();

        if (userInput == KEY_DOWN || userInput == 's')
        {
            if (tmp->lowerShape(gameMap))
            {
                checkRows();
                setPiece(tmp);
            }
            dropShape = 0;
        }
        else if (userInput == KEY_LEFT || userInput == 'a')
        {
            tmp->moveLeft(gameMap);
        }
        else if (userInput == KEY_RIGHT || userInput == 'd')
        {
            tmp->moveRight(gameMap);
        }
        else if (userInput == KEY_UP || userInput == 'w')
        {
            tmp->rotate(gameMap);
        }

        if (dropShape >= 800000)
        {
            if (tmp->lowerShape(gameMap))
            {
                checkRows();
                setPiece(tmp);
            }
            dropShape = 0;
        }

        // forTesting();

        usleep(usleepDelay);
        dropShape += usleepDelay;
        userInput = -1;
    }

    return 0;
}