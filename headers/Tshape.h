#ifndef TSHAPE_H
#define TSHAPE_H

#include "shape.h"

class Tshape : public Shape
{
protected:
    int rotation;

public:
    Tshape();
    virtual ~Tshape();
    void insertShape(char ch);
    void rotate(int gameMap[19][10]);
    int lowerShape(int gameMap[19][10]);
    void moveLeft(int gameMap[19][10]);
    void moveRight(int gameMap[19][10]);
};

#endif