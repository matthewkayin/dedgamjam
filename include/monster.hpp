#ifndef monster_h
#define monster_h

#include "Entity.hpp"

class Monster : public Entity{
public:
    Monster();
    
    int getHealth();
    
    void setHealth(int value);
    
private:
    int health;
    int mSpeed;
};

#endif /* monster_h */
