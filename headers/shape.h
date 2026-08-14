#ifndef SHAPE_H
#define SHAPE_H

#define ROWS 21
#define COLS 12

class Shape {
protected:
    int shapeY, shapeX, startY, startX, endY, endX;
public:
    Shape();
    virtual ~Shape();
    virtual void insertShape(char ch) = 0;
    virtual void rotate(int gameMap[19][10]) = 0;
    virtual int lowerShape(int gameMap[19][10]) = 0;
    virtual void moveLeft(int gameMap[19][10]) = 0;
    virtual void moveRight(int gameMap[19][10]) = 0;
};

#endif