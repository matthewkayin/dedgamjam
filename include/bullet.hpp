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
    float getX() const;
    float getY() const;
    float getDx() const;
    float getDy() const;
    float getDegree() const;
private:
    const float SPEED = 15;
    Bullet *next;
    Bullet *prev;
    float x;
    float y;
    float dx;
    float dy;
    float degree;
};

#endif
