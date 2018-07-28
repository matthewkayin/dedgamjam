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
    
private:
    int fuel;
    int ammo;
    Uint32 timeSinceBoost;
    Uint32 boostDelay;
};



#endif /* Player_h */
