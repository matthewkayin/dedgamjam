//
//  monster.cpp
//  GameJamMaybe
//
//  Created by Zubair Khan on 7/28/18.
//  Copyright © 2018 Zubair Khan. All rights reserved.
//

#include "monster.hpp"

Monster::Monster()
{
    head = nullptr;
    tail = nullptr;
    setDx(0);
    setDy(0);
    health = 3;
    setImageCode(MONSTER, 48, 48);
    mSpeed = 1;
}

int Monster::getHealth(){

    return health;
}

Monster* Monster::getHead(){

    return head;
}

Monster* Monster::getTail(){

    return tail;
}

void Monster::setHealth(int value){

    health = value;
}

void Monster::setHead(Monster* newHead){

    head = newHead;
}

void Monster::setTail(Monster* newTail){

    tail = newTail;
}
