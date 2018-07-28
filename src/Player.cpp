#include "Player.hpp"

Player::Player(){
    
    setX(<#int value#>);
    setY(<#int value#>);
    setDx(<#int value#>);
    setDy(<#int value#>);
    setHealth(<#int value#>);
    setImageCode(PLAYER, 64, 64)
    timeSinceBoost = SDL_GetTicks();
    boostDelay = 5000; //we can change this to increase time between boosts
}

Player::~Player(){
    
    
}

void Player::fireShot(){
    
    if (ammo <= 0)
        //out of ammo output to screen
    
    if (ammo > 0)
        //fire ammo
}

void Player::getFuel(){
    
    return fuel
}

bool Player::useBoost(){
    if((SDL_GetTicks() - timeSinceBoost() >= 5000) && (fuel > /*enter value for boost here*/)){
        
        fuel -= /*value above*/;
        timeSinceBoost = SDL_GetTicks();
    }
    
    else{
        
        //output that can't use boost
    }
}
