#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include <cmath>

class Player : public Entity
{
public:
    Player();
    Player(Uint32 currentTime);
    void updatePosition(Uint32 currentTime, int delta);
    int getSpeed() const;

private:

    int maxPlayerSpeed;
    int playerSpeed = 5;
    Uint32 acceltick;
};



#endif /* Player_h */
