#ifndef monster_h
#define monster_h

#include "Entity.hpp"
#include <cstdlib>

class Monster : public Entity{
public:
    Monster();
    
    int getHealth();
    Monster* getHead();
    Monster* getTail();
    
    void setHealth(int value);
    void setHead(Monster* newHead);
    void setTail(Monster* newTail);
    
private:
    int health;
    int mSpeed;
    Monster* head;
    Monster* tail;
};

#endif /* monster_h */
