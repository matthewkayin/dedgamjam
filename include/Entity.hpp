#ifndef Entity_hpp
#define Entity_hpp

#include "global.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
    int getHealth();
    ImgCode getImageCode();

    void setX(int value);
    void setY(int value);
    void setDx(int value);
    void setDy(int value);
    void setHealth(int value);
    void setImageCode(ImgCode value, int w, int h);

    bool getCollision(Entity &other);

private:
    ImgCode imgCode;
    int x;
    int y;
    int xSpeed;
    int ySpeed;
    int health;
    int width;
    int height;
};

#endif /* Entity_hpp */
