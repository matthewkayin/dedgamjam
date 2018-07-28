#ifndef Player_h
#define Player_h
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();
    ~Player();

    int getFuel();
    void fireShot();

    int getPlayerSpeed();

private:
    int fuel;
    int ammo;
    int playerSpeed;
    Uint32 timeSinceBoost;
    Uint32 boostDelay;
};



#endif /* Player_h */
