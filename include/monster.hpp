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
    int getMonsterType();

    void setHealth(int value);
    void setUse(bool value);
    void setDegree(float value);
    void setMonsterType(int value);
    float getDegree() const;

private:
    int health;
    int mSpeed;
    bool inUse;
    float degree;
    int monsterType;
};

#endif /* monster_h */
