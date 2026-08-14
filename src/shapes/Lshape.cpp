#include <ncurses.h>
#include <cstdlib>
#include "shape.h"
#include "Lshape.h"

Lshape::Lshape() {
    this->shapeY = 0;
    this->shapeX = 4;
    this->rotation = 0;

    getmaxyx(stdscr, endY, endX);
    startY = (endY - ROWS) / 2;
    startX = (endX - COLS) / 2;
    
    insertShape('#');
    refresh();
}

Lshape::~Lshape() {}

void Lshape::insertShape(char ch) {
    int i;

    attron(COLOR_PAIR(4));
    if (rotation == 0) {
        mvaddch(startY + shapeY + 1, startX + shapeX + 2, ch);
        for (i = 0; i < 3; ++i) {
            mvaddch(startY + shapeY + 2, startX + shapeX + i, ch);
        }
    } else if (rotation == 1) {
        mvaddch(startY + shapeY + 2, startX + shapeX + 1, ch);
        for (i = 0; i < 3; ++i) {
            mvaddch(startY + shapeY + i, startX + shapeX, ch);
        }
    } else if (rotation == 2) {
        mvaddch(startY + shapeY + 1, startX + shapeX, ch);
        for (i = 0; i < 3; ++i) {
            mvaddch(startY + shapeY, startX + shapeX + i, ch);
        }
    } else if (rotation == 3) {
        mvaddch(startY + shapeY, startX + shapeX + 1, ch);
        for (i = 0; i < 3; ++i) {
            mvaddch(startY + shapeY + i, startX + shapeX + 2, ch);
        }
    }
    attroff(COLOR_PAIR(4));
    refresh();
}

void Lshape::rotate(int gameMap[19][10]) 
{
    if (rotation == 0 && shapeY < 17) {
        if (gameMap[shapeY + 1][shapeX] == 0 && gameMap[shapeY - 1][shapeX - 1] == 0 && gameMap[shapeY][shapeX - 1] == 0 && gameMap[shapeY + 1][shapeX - 1] == 0) {
            insertShape(' ');
            ++rotation;
            insertShape('#');
        }
    } else  if (rotation == 1 && shapeX < 9) {
        if (gameMap[shapeY][shapeX - 1] == 0 && gameMap[shapeY - 1][shapeX - 1] == 0 && gameMap[shapeY - 1][shapeX] == 0 && gameMap[shapeY - 1][shapeX + 1] == 0) {
            insertShape(' ');
            ++rotation;
            insertShape('#');
        }
    } else if (rotation == 2 && shapeY < 17) {
        if (gameMap[shapeY - 1][shapeX] == 0 && gameMap[shapeY - 1][shapeX + 1] == 0 && gameMap[shapeY][shapeX + 1] == 0 && gameMap[shapeY + 1][shapeX + 1] == 0) {
            insertShape(' ');
            ++rotation;
            insertShape('#');
        }
    } else if (rotation == 3 && shapeX > 0) {
        if (gameMap[shapeY][shapeX + 1] == 0 && gameMap[shapeY + 1][shapeX - 1] == 0 && gameMap[shapeY + 1][shapeX] == 0 && gameMap[shapeY + 1][shapeX + 1] == 0) {
            insertShape(' ');
            rotation = 0;
            insertShape('#');
        }
    }
}

int Lshape::lowerShape(int gameMap[19][10]) {
    int counter = 0;
     if (rotation == 0 && (gameMap[shapeY + 2][shapeX - 1] != 0 || gameMap[shapeY + 2][shapeX] != 0 || gameMap[shapeY + 2][shapeX + 1] != 0 || shapeY + 2 >= 19)) {
        gameMap[shapeY][shapeX + 1] = 4;
        gameMap[shapeY + 1][shapeX - 1] = 4;
        gameMap[shapeY + 1][shapeX] = 4;
        gameMap[shapeY + 1][shapeX + 1] = 4;

        ++counter;
    } else if (rotation == 1 && (gameMap[shapeY + 2][shapeX] != 0 || gameMap[shapeY + 2][shapeX - 1] != 0 || shapeY + 2 >= 19)) {
        gameMap[shapeY + 1][shapeX] = 4;
        gameMap[shapeY - 1][shapeX - 1] = 4;
        gameMap[shapeY][shapeX - 1] = 4;
        gameMap[shapeY + 1][shapeX - 1] = 4;

        ++counter;
    } else if (rotation == 2 && (gameMap[shapeY + 1][shapeX - 1] != 0 || gameMap[shapeY][shapeX] != 0 || gameMap[shapeY][shapeX + 1] != 0 || shapeY + 1 >= 19)) {
        gameMap[shapeY][shapeX - 1] = 4;
        gameMap[shapeY - 1][shapeX - 1] = 4;
        gameMap[shapeY - 1][shapeX] = 4;
        gameMap[shapeY - 1][shapeX + 1] = 4;

        ++counter;
    } else if (rotation == 3 && (gameMap[shapeY][shapeX] != 0 || gameMap[shapeY + 2][shapeX + 1] != 0 || shapeY + 2 >= 19)) {
        gameMap[shapeY - 1][shapeX] = 4;
        gameMap[shapeY - 1][shapeX + 1] = 4;
        gameMap[shapeY][shapeX + 1] = 4;
        gameMap[shapeY + 1][shapeX + 1] = 4;

        ++counter;
    }

    if (shapeY == 0 && counter > 0) {
        mvaddstr(startY + 6, startX -13, "Game over! Press any key to continue");
        nodelay(stdscr, false);
        refresh();
        getch();
        endwin();
        exit(0);
    } else if (counter > 0) {
        return 1;
    }

    insertShape(' ');
    ++shapeY;
    insertShape('#');

    return 0;
}

void Lshape::moveLeft(int gameMap[19][10]) {
    if (rotation == 0 && shapeX > 1 && gameMap[shapeY][shapeX] == 0 && gameMap[shapeY + 1][shapeX - 2] == 0) {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    } else if (rotation == 1 && shapeX >= 2 && gameMap[shapeY - 1][shapeX - 2] == 0 && gameMap[shapeY][shapeX - 2] == 0 && gameMap[shapeY + 1][shapeX - 2] == 0) {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    } else if (rotation == 2 && shapeX > 1 && gameMap[shapeY][shapeX - 2] == 0 && gameMap[shapeY - 1][shapeX - 2] == 0) {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    } else if (rotation == 3 && shapeX >= 1 && gameMap[shapeY - 1][shapeX - 1] == 0 && gameMap[shapeY][shapeX] == 0 && gameMap[shapeY + 1][shapeX] == 0) {
        insertShape(' ');
        --shapeX;
        insertShape('#');
    }
}

void Lshape::moveRight(int gameMap[19][10]) {
    if (rotation == 0 && shapeX < 8 && gameMap[shapeY][shapeX + 2] == 0 && gameMap[shapeY + 1][shapeX + 2] == 0) {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    } else if (rotation == 1 && shapeX <= 8 && gameMap[shapeY - 1][shapeX] == 0 && gameMap[shapeY][shapeX] == 0 && gameMap[shapeY + 1][shapeX + 1] == 0) {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    } else if (rotation == 2 && shapeX < 8 && gameMap[shapeY][shapeX] == 0 && gameMap[shapeY - 1][shapeX + 2] == 0) {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    } else if (rotation == 3 && shapeX <= 7 && gameMap[shapeY - 1][shapeX + 2] == 0 && gameMap[shapeY][shapeX + 2] == 0 && gameMap[shapeY + 1][shapeX + 2] == 0) {
        insertShape(' ');
        ++shapeX;
        insertShape('#');
    }
}