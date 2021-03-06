#ifndef ENTITY_H
#define ENTITY_H

#include "global.hpp"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>

class Entity {
public:
    Entity();

    void updatePosition(int delta);

    int getX();
    int getY();
    int getDX();
    int getDY();
    int getWidth();
    int getHeight();
    ImgCode getImageCode();

    void setX(int value);
    void setY(int value);
    void setDx(int value);
    void setDy(int value);
    void setImageCode(ImgCode value, int w, int h);

    bool getCollision(Entity &other);

private:
    ImgCode imgCode;
    int x;
    int y;
    int xSpeed;
    int ySpeed;
    int width;
    int height;
};

#endif /* Entity_hpp */
