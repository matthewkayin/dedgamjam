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
    BULLET,
    MONSTER
};

#endif
