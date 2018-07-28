//level class, where everything will happen
//level will be update logic only

#ifndef LEVEL_H
#define LEVEL_H
#include "Player.hpp"

#include "chunk.hpp"

class Level{

public:
    Level();
    Level(int screenwidth, int screenheight);
    int getCameraXOffset() const;
    int getCameraYOffset() const;
    Chunk* getChunkFromPosition(int x, int y);
    
    Player getPlayer();
    

private:
    Chunk* base;
    int chunkwidth;
    int chunkheight;
    int cameraxOffset;
    int camerayOffset;
    Player player;
};

#endif
