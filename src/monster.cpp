//
//  monster.cpp
//  GameJamMaybe
//
//  Created by Zubair Khan on 7/28/18.
//  Copyright © 2018 Zubair Khan. All rights reserved.
//

#include "monster.hpp"

Monster::Monster(){
    setDx(0);
    setDy(0);
    health = 3;
    setImageCode(MONSTER, 48, 48);
    mSpeed = 4;
    inUse = false;
}

int Monster::getHealth(){

    return health;
}

bool Monster::beingUsed(){

    return inUse;
}

int Monster::getSpeed(){

    return mSpeed;
}

void Monster::setHealth(int value){

    health = value;
}

void Monster::setUse(bool value){

    inUse = value;
}

void Monster::setDegree(float value){

    degree = value;
}

float Monster::getDegree() const{

    return degree;
}
