//level class, where everything will happen
//level will be update logic only

#ifndef LEVEL_H
#define LEVEL_H
#include "Player.hpp"

class Level{

public:
    Level();
    
    void setPlayerSpeedX(int value);
    void setPlayerSpeedY(int value);
    

private:
    int chunkwidth;
    int chunkheight;
    Player player1;
};

#endif
