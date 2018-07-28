//This file contains global functions to be used across classes rather than writing a function in each one

#ifndef GLOBAL_H
#define GLOBAL_H

#include <cmath>

inline float toRadians(float degree){

    return degree * (M_PI / 180);
}

enum ImgCode{
    GRASS,
    PLAYER,
    BULLET
};

bool getRectangleCollision(int x, int y, int width, int height, int xtwo, int ytwo, int widthtwo, int heighttwo){

    int xpoint = x;
    int ypoint = y;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    xpoint = x + width;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    ypoint = y + height;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    xpoint = x - width;
    if ( xpoint >= xtwo && xpoint <= xtwo + widthtwo && ypoint >= ytwo && ypoint <= ytwo + heighttwo ){

        return true;
    }

    return false;
}

#endif
