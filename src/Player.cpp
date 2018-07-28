#include "Player.hpp"

Player::Player(){
    
    setDx(0);
    setDy(0);
    setHealth(10);
    /*setImageCode(PLAYER, 64, 64)
    timeSinceBoost = SDL_GetTicks();
    boostDelay = 5000; //we can change this to increase time between boosts*/
}

Player::~Player(){
    
    
}

int Player::getFuel(){
    
    return fuel;
}

void Player::fireShot(){
    
}
