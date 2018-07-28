//bullet class, used to keep track of player bullets in a linkedlist

#ifndef BULLET_H
#define BULLET_H

#include "global.hpp"
#include <cmath>
#include <iostream>

class Bullet{

public:
    Bullet(int xi, int yi, float di);
    void updatePosition(int delta);
    Bullet* getNext() const;
    Bullet* getPrev() const;
    void setNext(Bullet *other);
    void setPrev(Bullet *other);
    int getX() const;
    int getY() const;
    float getDegree() const;
private:
    const float SPEED = 15;
    Bullet *next;
    Bullet *prev;
    int x;
    int y;
    int dx;
    int dy;
    float degree;
};

#endif
