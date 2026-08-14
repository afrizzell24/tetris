#ifndef ISHAPE_H
#define ISHAPE_H

#include "shape.h"

class Ishape : public Shape
{
protected:
    int rotation;

public:
    Ishape();
    virtual ~Ishape();
    void insertShape(char ch);
    void rotate(int gameMap[19][10]);
    int lowerShape(int gameMap[19][10]);
    void moveLeft(int gameMap[19][10]);
    void moveRight(int gameMap[19][10]);
};

#endif