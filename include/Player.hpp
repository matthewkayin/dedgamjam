#ifndef Player_h
#define Player_h
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player();
    ~Player();
    
    void fireShot();
    void getFuel();
    bool useBoost();
    void resetBoost();
    
private:
    int fuel;
    int ammo;
    Uint32 timeSinceBoost;
    Uint32 boostDelay;
};



#endif /* Player_h */
