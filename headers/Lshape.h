#ifndef LSHAPE_H
#define LSHAPE_H

#include "shape.h"

class Lshape : public Shape
{
protected:
    int rotation;

public:
    Lshape();
    virtual ~Lshape();
    void insertShape(char ch);
    void rotate(int gameMap[19][10]);
    int lowerShape(int gameMap[19][10]);
    void moveLeft(int gameMap[19][10]);
    void moveRight(int gameMap[19][10]);
};

#endif