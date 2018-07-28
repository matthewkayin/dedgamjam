#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();

    int getFuel();
    void fireShot();

    int getPlayerSpeed();

private:
    int fuel;
    int ammo;
    
    int maxPlayerSpeed;
    int playerSpeed;
    Uint32 timeSinceBoost;
    Uint32 boostDelay;
};



#endif /* Player_h */
