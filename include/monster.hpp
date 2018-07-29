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
    void setDegree(float value);
    float getDegree() const;

private:
    int health;
    int mSpeed;
    bool inUse;
    float degree;
};

#endif /* monster_h */
