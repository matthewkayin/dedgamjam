#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();

    int getFuel();
    int getHealth();
    
    void fireShot();
    void setHealth(int value);
    
    int getPlayerSpeed();

private:
    int fuel;
    int ammo;
    
    int maxPlayerSpeed;
    int playerSpeed;
    int health;
    Uint32 timeSinceBoost;
    Uint32 boostDelay;
};



#endif /* Player_h */
