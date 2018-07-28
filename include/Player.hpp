#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include "bullet.hpp"
#include <cmath>

class Player : public Entity
{
public:
    Player();
    Player(Uint32 currentTime);
    void updatePosition(Uint32 currentTime, int delta, int screenwidth, int screenheight);
    int getSpeed() const;
    void shoot(float degree);
    Bullet* getHead();
    void killBullet(Bullet *bullet);

private:
    Bullet *head;
    int maxPlayerSpeed;
    int playerSpeed = 5;
    Uint32 acceltick;
};



#endif /* Player_h */
