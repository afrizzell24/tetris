#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class square : public Shape {
protected:
public:
    square();
    virtual ~square();
    void insertShape(char ch);
    void rotate(int gameMap[19][10]);
    int lowerShape(int gameMap[19][10]);
    void moveLeft(int gameMap[19][10]);
    void moveRight(int gameMap[19][10]);
};

#endif