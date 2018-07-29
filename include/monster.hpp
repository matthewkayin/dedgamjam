#ifndef monster_h
#define monster_h

#include "Entity.hpp"
#include <cstdlib>
#include <cmath>

class Monster : public Entity{
public:
    Monster();
    
    int getHealth();
    bool beingUsed();
    int getSpeed();
    
    void setHealth(int value);
    void setUse(bool value);
    
private:
    int health;
    int mSpeed;
    bool inUse;
};

#endif /* monster_h */
