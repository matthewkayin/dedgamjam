#include "Player.hpp"

Player::Player(){

    setDx(0);
    setDy(0);
    health = 10;
    setImageCode(PLAYER, 64, 64);
    playerSpeed = 3; //this is going to be waay too high lol
    /*timeSinceBoost = SDL_GetTicks();
    boostDelay = 5000; //we can change this to increase time between boosts*/
}

int Player::getHealth(){
    
    return health;
}

int Player::getFuel(){

    return fuel;
}

void Player::fireShot(){

}

void Player::setHealth(int value){
    
    health = value;
}

int Player::getPlayerSpeed(){

    return playerSpeed;
}

