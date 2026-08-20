#ifndef ZSHAPE_H
#define ZSHAPE_H

#include "shape.h"

class Zshape : public Shape
{
protected:
    int rotation;

public:
    Zshape();
    virtual ~Zshape();
    void insertShape(char ch);
    void rotate(int gameMap[19][10]);
    int lowerShape(int gameMap[19][10]);
    void moveLeft(int gameMap[19][10]);
    void moveRight(int gameMap[19][10]);
};

#endif