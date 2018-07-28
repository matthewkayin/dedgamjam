#include "Player.hpp"

Player::Player(){

    setDx(0);
    setDy(0);
    setImageCode(PLAYER, 64, 64);
    maxPlayerSpeed = 5;
    playerSpeed = 5;
    acceltick = 0;
}

Player::Player(Uint32 currentTime){

    setDx(0);
    setDy(0);
    setImageCode(PLAYER, 64, 64);
    maxPlayerSpeed = 5;
    playerSpeed = 5;
    acceltick = currentTime;
}

void Player::updatePosition(Uint32 currentTime, int delta){

    setX(getX() + (getDX() * delta));
    setY(getY() + (getDY() * delta));
}

int Player::getSpeed() const{

    return playerSpeed;
}
