#include "bullet.hpp"

Bullet::Bullet(int xi, int yi, float di){

    x = xi;
    y = yi;
    degree = di - 90;
    if(degree >= 360){

        degree -= 360;

    }else if(degree < 0){

        degree += 360;
    }
    degree = 360 - degree;
    dx = cos(toRadians(degree)) * SPEED;
    dy = sin(toRadians(degree)) * -SPEED;

    next = nullptr;
    prev = nullptr;
}

void Bullet::updatePosition(int delta){

    x += (dx * delta);
    y += (dy * delta);
}

Bullet* Bullet::getNext() const{

    return next;
}

Bullet* Bullet::getPrev() const{

    return prev;
}

void Bullet::setNext(Bullet *other){

    next = other;
}

void Bullet::setPrev(Bullet *other){

    prev = other;
}

int Bullet::getX() const{

    return x;
}

int Bullet::getY() const{

    return y;
}

int Bullet::getDx() const{

    return dx;
}

int Bullet::getDy() const{

    return dy;
}

float Bullet::getDegree() const{

    return degree;
}
