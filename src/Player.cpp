#include "Player.hpp"

Player::Player(){

    setDx(0);
    setDy(0);
    setImageCode(PLAYER, 64, 64);
    maxPlayerSpeed = 5;
    playerSpeed = 5;
    acceltick = 0;
    head = nullptr;
    isDead = false;
    score = 0;
}

Player::Player(Uint32 currentTime){

    setDx(0);
    setDy(0);
    setImageCode(PLAYER, 64, 64);
    maxPlayerSpeed = 5;
    playerSpeed = 5;
    acceltick = currentTime;
    head = nullptr;
    isDead = false;
    score = 0;
}

void Player::updatePosition(Uint32 currentTime, int delta, int screenwidth, int screenheight){

    setX(getX() + (getDX() * delta));
    setY(getY() + (getDY() * delta));

    if(getX() <= 0){

        setX(0);

    }else if(getX() + getWidth() >= screenwidth){

        setX(screenwidth - getWidth());
    }

    if(getY() <= 0){

        setY(0);

    }else if(getY() + getHeight() >= screenheight){

        setY(screenheight - getHeight());
    }

    Bullet *curr = head;

    while(curr != nullptr){

        curr->updatePosition(delta);

        if( ( curr->getX()  + 12 <= 0 || curr->getX() >= screenwidth ) &&
            ( curr->getY() + 12 <= 0 || curr->getY() >= screenheight ) ){

                Bullet *toSet = nullptr;
                if(curr->getNext() != nullptr){

                    toSet = curr->getNext();
                }
                killBullet(curr);
                curr = toSet;
            }

        if(curr != nullptr){

            curr = curr->getNext();
        }
    }
}

Bullet* Player::getHead(){

    return head;
}

void Player::killBullet(Bullet *bullet){

    if(bullet->getPrev() == nullptr){

        head = bullet->getNext();

    }else{

        (bullet->getPrev())->setNext(bullet->getNext());

        if(bullet->getNext() != nullptr){

            (bullet->getNext())->setPrev(bullet->getPrev());
        }
    }

    delete bullet;
}

void Player::shoot(float degree){

    Bullet *toMake = new Bullet(getX() + (getWidth() / 2), getY() + (getHeight() / 2), degree);

    if(head == nullptr){

        head = toMake;

    }else{

        Bullet *curr = head;

        while(curr->getNext() != nullptr){

            curr = curr->getNext();
        }

        curr->setNext(toMake);
    }
}

bool Player::getDead() const{

    return isDead;
}

void Player::setDead(bool value){

    isDead = value;
}

int Player::getSpeed() const{

    return playerSpeed;
}

int Player::getScore() const{

    return score;
}

void Player::countScore(){

    score++;
}
